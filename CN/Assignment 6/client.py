import socket
import cv2
import numpy as np
import pyaudio

SERVER_ADDR = ('127.0.0.1', 9999)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    print("1. Audio Stream")
    print("2. Video Stream")
    print("3. Exit")
    choice = int(input("Enter your choice (1, 2 or 3): "))

    if choice == 3:
        break
    
    if choice == 1:
        selection = 'audio'
    elif choice == 2:
        selection = 'video'
    else:
        print("Invalid choice")
        continue

    client_socket.sendto(selection.encode('utf-8'), SERVER_ADDR)

    if selection == 'video':
        while True:
            packet, _ = client_socket.recvfrom(65536)
            if packet == b"END_STREAM":
                break
            np_data = np.frombuffer(packet, dtype=np.uint8)
            frame = cv2.imdecode(np_data, cv2.IMREAD_COLOR)
            if frame is not None:
                cv2.imshow("Video Stream", frame)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
        cv2.destroyAllWindows()

    elif selection == 'audio':
        meta_packet, _ = client_socket.recvfrom(1024)
        rate, channels, width = map(int, meta_packet.decode().split(','))
        
        p = pyaudio.PyAudio()
        fmt = p.get_format_from_width(width)
        
        stream = p.open(format=fmt, channels=channels, rate=rate, output=True, frames_per_buffer=1024)
        
        client_socket.settimeout(2.0) 
        try:
            while True:
                try:
                    packet, _ = client_socket.recvfrom(8192)
                    if packet == b"END_STREAM":
                        break
                    stream.write(packet, exception_on_underflow=False)
                except socket.timeout:
                    break
        except KeyboardInterrupt:
            pass
        finally:
            stream.stop_stream()
            stream.close()
            p.terminate()
            client_socket.settimeout(None)

client_socket.close()
