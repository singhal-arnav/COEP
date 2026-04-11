import socket
import hashlib
import random
import time

RECEIVER_ADDRESS = ("localhost", 12345)
LOSS_PROBABILITY = 0.3
CORRUPT_PROBABILITY = 0.2
TIMEOUT = 2
SEQ_NO = 0

def cal_checksum(data):
    hash_obj = hashlib.sha256()
    hash_obj.update(data.encode())
    return hash_obj.hexdigest()

sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sender_socket.settimeout(TIMEOUT)

while True:
    try:
        message = input("Enter your message (or 'exit' to quit): ")
        is_exit = message.lower() == 'exit'

        ack_received = False
        while not ack_received:
            checksum = cal_checksum(message)
            packet = f"{message}:{checksum}:{SEQ_NO % 2}"

            if random.random() >= LOSS_PROBABILITY:
                sending_packet = packet
                if random.random() < CORRUPT_PROBABILITY:
                    bad_checksum = cal_checksum("CORRUPTED")
                    sending_packet = f"{message}:{bad_checksum}:{SEQ_NO % 2}"
                    print(f"Packet corrupted before sending (seq={SEQ_NO % 2}).")
                sender_socket.sendto(sending_packet.encode('utf-8'), RECEIVER_ADDRESS)
                print(f"Sent packet (seq={SEQ_NO % 2}).")
            else:
                print(f"Packet lost (simulated, seq={SEQ_NO % 2}).")

            if is_exit:
                ack_received = True
                SEQ_NO += 1
                break

            try:
                response, _ = sender_socket.recvfrom(1024)
                ack_msg, ack_checksum, ack_seq = response.decode('utf-8').split(':')
                ack_seq = int(ack_seq)

                if cal_checksum(ack_msg) != ack_checksum:
                    print("Corrupted ACK received. Retransmitting...")
                elif ack_seq != SEQ_NO % 2:
                    print(f"Wrong ACK seq (got {ack_seq}, expected {SEQ_NO % 2}). Retransmitting...")
                else:
                    print(f"ACK {ack_seq} received. Message delivered successfully.")
                    ack_received = True
                    SEQ_NO += 1

            except socket.timeout:
                print(f"Timeout. Retransmitting (seq={SEQ_NO % 2})...")

        if is_exit:
            print("Exiting.")
            break

    except Exception as e:
        print(f"Error: {e}")

sender_socket.close()
