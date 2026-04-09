import socket
import random

def selective_repeat_receiver():
    receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_socket.bind(('localhost', 12347))

    expected_seq_num = 0
    buffer = {}
    loss_probability = 0.3

    print("[SR Receiver] Listening...")

    while True:
        packet, sender_address = receiver_socket.recvfrom(1024)
        packet = packet.decode()

        if packet.startswith("END:"):
            print("[SR Receiver] Received END signal. Shutting down.")
            break

        seq_num, data = packet.split(":", 1)
        seq_num = int(seq_num)

        if random.random() < loss_probability:
            print(f"[SR Receiver] Packet {seq_num} lost (simulated).")
            continue

        if seq_num == expected_seq_num:
            print(f"[SR Receiver] Accepted in-order packet (Seq: {seq_num}, Data: {data})")
            receiver_socket.sendto(str(seq_num).encode(), sender_address)
            expected_seq_num += 1

            while expected_seq_num in buffer:
                seq, buf_data = buffer.pop(expected_seq_num)
                print(f"[SR Receiver] Delivered buffered packet (Seq: {seq}, Data: {buf_data})")
                expected_seq_num += 1

        elif seq_num > expected_seq_num:
            if seq_num not in buffer:
                print(f"[SR Receiver] Buffered out-of-order packet (Seq: {seq_num}, Data: {data})")
                buffer[seq_num] = (seq_num, data)
            receiver_socket.sendto(str(seq_num).encode(), sender_address)

    receiver_socket.close()


selective_repeat_receiver()
