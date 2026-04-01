import socket

SERVER_IP = '127.0.0.1' 
PORT = 8080

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    print(f"Connecting to {SERVER_IP}:{PORT}")
    client_socket.connect((SERVER_IP, PORT))

    message = "Hello from the client side!"
    print(f"Sending: {message}")
    client_socket.sendall(message.encode('utf-8'))

    data = client_socket.recv(1024).decode('utf-8')
    print(f"Received from server: {data}")

except ConnectionRefusedError:
    print("Error: Failed to connect to server.")
except Exception as e:
    print(f"Error: {e}")

finally:
    print("Closing connection.")
    client_socket.close()
