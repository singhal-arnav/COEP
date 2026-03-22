import socket
import threading
import sys

def receive_messages(sock):
    while True:
        try:
            data = sock.recv(1024).decode()
            if not data:
                print("\nPeer disconnected.")
                break
            print("\n" + data)
        except:
            print("\nConnection lost.")
            break
    sock.close()
    sys.exit()

def send_messages(sock, username):
    while True:
        msg = input()
        if msg.lower() == "exit":
            sock.send(f"{username} has left the chat.".encode())
            sock.close()
            sys.exit()
        full_msg = f"{username}: {msg}"
        sock.send(full_msg.encode())

def start_server(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("", port))
    server.listen(1)
    print(f"Listening on port {port}...")
    conn, addr = server.accept()
    print(f"Connected with {addr}")
    return conn

def start_client(ip, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))
    print("Connected to peer.")
    return client

if __name__ == "__main__":
    mode = input("Enter mode (listen/connect): ").strip().lower()
    username = input("Enter your username: ")

    if mode == "listen":
        port = int(input("Enter port to listen on: "))
        sock = start_server(port)

    elif mode == "connect":
        ip = input("Enter peer IP: ")
        port = int(input("Enter peer port: "))
        sock = start_client(ip, port)

    else:
        print("Invalid mode.")
        sys.exit()

    threading.Thread(target=receive_messages, args=(sock,), daemon=True).start()
    send_messages(sock, username)
