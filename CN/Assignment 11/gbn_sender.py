import socket
import time

def go_back_n_sender(data, window_size, timeout=2):
    sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_address = ('localhost', 12346)

    base = 0
    next_seq_num = 0
    total_transmissions = 0
    window_timer = None

    while base < len(data):
        while next_seq_num < base + window_size and next_seq_num < len(data):
            packet = f"{next_seq_num}:{data[next_seq_num]}"
            sender_socket.sendto(packet.encode(), receiver_address)
            print(f"[GBN Sender] Sent packet (Seq: {next_seq_num}, Data: {data[next_seq_num]})")
            total_transmissions += 1
            if base == next_seq_num:
                window_timer = time.time()
            next_seq_num += 1

        try:
            sender_socket.settimeout(timeout)
            ack, _ = sender_socket.recvfrom(1024)
            ack_num = int(ack.decode())
            
            print(f"[GBN Sender] Received ACK {ack_num}")
            if ack_num >= base:
                base = ack_num + 1
                window_timer = time.time() if base < len(data) else None
        except socket.timeout:
            print(f"[GBN Sender] Timeout! Resending window from base={base}")
            next_seq_num = base
            window_timer = time.time()

    end_packet = f"END:END"
    sender_socket.sendto(end_packet.encode(), receiver_address)
    sender_socket.close()
    print(f"\n[GBN Sender] All packets delivered. Total transmissions: {total_transmissions}")
    return total_transmissions


data = ["P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"]
go_back_n_sender(data, window_size=4)
