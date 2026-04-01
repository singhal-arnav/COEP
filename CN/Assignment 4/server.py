import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', 8080))
server_socket.listen(5)

print("Server is running on port 8080...")

try:
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"New connection from: {client_address}")
        
        message = client_socket.recv(1024).decode('utf-8')
        
        if message:
            print(f"Client said: {message}")
            
            response = f"Server received your message: '{message}'"
            client_socket.sendall(response.encode('utf-8'))
        
        client_socket.close()

except KeyboardInterrupt:
    print("\nShutting down the server...")

finally:
    server_socket.close()
