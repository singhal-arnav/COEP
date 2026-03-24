import socket
import sys

def check(response, expected):
    if not response.startswith(str(expected)):
    	print("Server returned an unexpected response. Terminating.")
    	sys.exit()

server = "localhost"
port = 1025

sender = input("Enter sender email: ")
recipient = input("Enter recipient email: ")
subject = input("Enter subject: ")

print("Enter message body (end with a single '.' on a line):")
lines = []
while True:
    line = input()
    lines.append(line)
    if line == ".":
        break

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((server, port))

resp = client.recv(1024).decode()
check(resp, 220)

client.send(("HELO localhost\r\n").encode())
resp = client.recv(1024).decode()
check(resp, 250)

client.send((f"MAIL FROM:<{sender}>\r\n").encode())
resp = client.recv(1024).decode()
check(resp, 250)

client.send((f"RCPT TO:<{recipient}>\r\n").encode())
resp = client.recv(1024).decode()
check(resp, 250)

client.send(("DATA" + "\r\n").encode())
resp = client.recv(1024).decode()
check(resp, 354)

client.send((f"From: {sender}\r\n").encode())
client.send((f"To: {recipient}\r\n").encode())
client.send((f"Subject: {subject}\r\n").encode())
client.send(("\r\n").encode())

for line in lines:
    client.send((line + "\r\n").encode())

resp = client.recv(1024).decode()
check(resp, 250)

print("Mail sent successfully!")

client.send(("QUIT\r\n").encode())
client.recv(1024)

client.close()

