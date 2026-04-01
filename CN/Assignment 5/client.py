import socket

SERVER_IP = '127.0.0.1' 
PORT = 8080

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    client_socket.connect((SERVER_IP, PORT))

    http_request = (
        "GET / HTTP/1.1\r\n"
        f"Host: {SERVER_IP}\r\n"
        "Connection: close\r\n"
        "\r\n"
    )
    
    client_socket.sendall(http_request.encode('utf-8'))

    response = client_socket.recv(4096).decode('utf-8')
    print("Server response:")
    print(response)

except Exception as e:
    print(f"Connection error: {e}")
finally:
    client_socket.close()
