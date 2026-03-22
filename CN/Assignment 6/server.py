import socket
import cv2
import time
import wave

SERVER_IP = '127.0.0.1'
PORT = 9999
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((SERVER_IP, PORT))

print(f"UDP Stream Server listening on {PORT}...")

while True:
    data, client_address = server_socket.recvfrom(1024)
    choice = data.decode('utf-8').lower()
    
    if choice == 'video':
        cap = cv2.VideoCapture("sample_video.mp4")
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                break
            
            frame = cv2.resize(frame, (720, 480))
            
            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 40])
            
            try:
                server_socket.sendto(buffer, client_address)
            except OSError:
                continue
            time.sleep(0.03)
            
        cap.release()
        server_socket.sendto(b"END_STREAM", client_address)
        print("Video stream finished")
        
    elif choice == 'audio':
        wf = wave.open("sample_audio.wav", 'rb')
        meta = f"{wf.getframerate()},{wf.getnchannels()},{wf.getsampwidth()}"
        server_socket.sendto(meta.encode(), client_address)
        time.sleep(0.2)
        
        data = wf.readframes(1024)
        while data:
            server_socket.sendto(data, client_address)
            data = wf.readframes(1024)
            time.sleep(0.8 * (1024 / wf.getframerate())) 
        
        wf.close()
        server_socket.sendto(b"END_STREAM", client_address)
        print("Audio stream finished")
