import socket
import threading
import sys

def receive_messages(sock, stop_event):
    while not stop_event.is_set():
        try:
            data = sock.recv(1024).decode()
            if not data:
                stop_event.set()
                break
            print(data)
        except:
            if not stop_event.is_set():
                print("\nConnection lost.")
            stop_event.set()
            break

def send_messages(sock, username, stop_event):
    while not stop_event.is_set():
        try:
            msg = input()
        except EOFError:
            stop_event.set()
            break

        if stop_event.is_set():
            break

        if msg.lower() in ("/leave", "/exit"):
            try:
                sock.send(f"{username} has left the chat. Press enter to continue.".encode())
            except:
                pass
            stop_event.set()
            return "/exit" if msg.lower() == "/exit" else None

        try:
            sock.send(f"{username}: {msg}".encode())
        except:
            stop_event.set()
            break

    return None

def start_server(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("", port))
    server.listen(1)
    print(f"Listening on port {port}...")
    conn, addr = server.accept()
    print(f"Connected with {addr}")
    server.close()
    return conn

def start_client(ip, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))
    print("Connected to peer.")
    return client


username = input("Enter your username: ")

while True:
    print("\nEnter 1 to wait for connection request")
    print("Enter 2 to connect to peer")
    print("Enter 'exit' to exit the application")
    mode = input().strip().lower()
    if mode == "exit":
        break

    if mode == "1":
        port = int(input("Enter port to listen on: "))
        sock = start_server(port)
    elif mode == "2":
        ip = input("Enter peer IP: ")
        port = int(input("Enter peer port: "))
        sock = start_client(ip, port)
    else:
        print("Invalid mode.")
        continue

    stop_event = threading.Event()

    threading.Thread(
        target=receive_messages,
        args=(sock, stop_event),
        daemon=True
    ).start()

    result = send_messages(sock, username, stop_event)
    sock.close()

    if result == "/exit":
        break
