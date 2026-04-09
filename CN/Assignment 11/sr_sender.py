import socket
import time

def selective_repeat_sender(data, window_size, timeout=2):
    sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_address = ('localhost', 12347)

    base = 0
    next_seq_num = 0
    acked = [False] * len(data)
    timers = [None] * len(data)
    total_transmissions = 0

    def send_packet(seq):
        nonlocal total_transmissions
        packet = f"{seq}:{data[seq]}"
        sender_socket.sendto(packet.encode(), receiver_address)
        timers[seq] = time.time()
        total_transmissions += 1
        print(f"[SR Sender] Sent packet (Seq: {seq}, Data: {data[seq]})")

    while base < len(data):
        while next_seq_num < base + window_size and next_seq_num < len(data):
            send_packet(next_seq_num)
            next_seq_num += 1

        sender_socket.settimeout(0.1)
        try:
            ack, _ = sender_socket.recvfrom(1024)
            ack_num = int(ack.decode())
            if 0 <= ack_num < len(data) and not acked[ack_num]:
                print(f"[SR Sender] Received ACK {ack_num}")
                acked[ack_num] = True
                while base < len(data) and acked[base]:
                    base += 1
        except socket.timeout:
            pass

        for i in range(base, next_seq_num):
            if not acked[i] and timers[i] is not None and time.time() - timers[i] > timeout:
                print(f"[SR Sender] Timeout! Resending packet (Seq: {i})")
                send_packet(i)

    end_packet = "END:END"
    sender_socket.sendto(end_packet.encode(), receiver_address)
    sender_socket.close()
    print(f"\n[SR Sender] All packets delivered. Total transmissions: {total_transmissions}")
    return total_transmissions


data = ["P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"]
selective_repeat_sender(data, window_size=4)
