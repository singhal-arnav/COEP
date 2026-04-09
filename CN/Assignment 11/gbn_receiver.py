import socket
import random

def go_back_n_receiver():
    receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_socket.bind(('localhost', 12346))

    expected_seq_num = 0
    loss_probability = 0.3
    last_ack_sent = -1

    print("[GBN Receiver] Listening...")

    while True:
        packet, sender_address = receiver_socket.recvfrom(1024)
        packet = packet.decode()

        if packet.startswith("END:"):
            print("[GBN Receiver] Received END signal. Shutting down.")
            break

        seq_num, data = packet.split(":", 1)
        seq_num = int(seq_num)

        if random.random() < loss_probability:
            print(f"[GBN Receiver] Packet {seq_num} lost (simulated).")
            continue

        if seq_num == expected_seq_num:
            print(f"[GBN Receiver] Accepted packet (Seq: {seq_num}, Data: {data})")
            receiver_socket.sendto(str(seq_num).encode(), sender_address)
            last_ack_sent = seq_num
            expected_seq_num += 1
        else:
            print(f"[GBN Receiver] Out-of-order packet (Seq: {seq_num}), expected {expected_seq_num}. Discarding.")
            if last_ack_sent >= 0:
                receiver_socket.sendto(str(last_ack_sent).encode(), sender_address)

    receiver_socket.close()


go_back_n_receiver()
