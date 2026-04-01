import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', 8080))
server_socket.listen(5)

print("HTTP Server running on port 8080...")

try:
    while True:
        client_socket, client_address = server_socket.accept()
        
        request = client_socket.recv(1024).decode('utf-8')
        if request:
            print(f"Request from {client_address}: {request.splitlines()[0]}")
            
            status_line = "HTTP/1.1 200 OK\r\n"
            headers = "Content-Type: text/html; charset=utf-8\r\n"
            body = "<html><body><h1>Hello World!</h1></body></html>"
            
            full_response = status_line + headers + "\r\n" + body
            
            client_socket.sendall(full_response.encode('utf-8'))
        
        client_socket.close()

except KeyboardInterrupt:
    print("\nShutting down server...")
finally:
    server_socket.close()
