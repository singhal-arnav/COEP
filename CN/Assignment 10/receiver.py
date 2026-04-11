import socket
import hashlib
import random

RECEIVER_PORT = 12345
LOSS_PROBABILITY = 0.3
CORRUPT_PROBABILITY = 0.2

def cal_checksum(data):
    hash_obj = hashlib.sha256()
    hash_obj.update(data.encode())
    return hash_obj.hexdigest()

receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_socket.bind(("localhost", RECEIVER_PORT))
print(f"Listening on localhost:{RECEIVER_PORT}")

expected_seq = 0

while True:
    try:
        data, sender_address = receiver_socket.recvfrom(1024)
        message, checksum, seq_no = data.decode('utf-8').split(':')
        seq_no = int(seq_no)

        if cal_checksum(message) != checksum:
            print("Received corrupted packet. Discarding (no ACK sent).")
            continue

        if seq_no != expected_seq % 2:
            print(f"Received duplicate (seq={seq_no}). Resending ACK {seq_no}.")
            ack_checksum = cal_checksum("ACK")
            packet = f"ACK:{ack_checksum}:{seq_no}"
            if random.random() >= LOSS_PROBABILITY:
                if random.random() < CORRUPT_PROBABILITY:
                    bad_checksum = cal_checksum("CORRUPTED")
                    packet = f"ACK:{bad_checksum}:{seq_no}"
                    print(f"ACK {seq_no} corrupted before sending.")
                receiver_socket.sendto(packet.encode(), sender_address)
            else:
                print(f"ACK {seq_no} lost (simulated).")
            continue

        print(f"Received: \"{message}\" (seq={seq_no}). Sending ACK {seq_no}.")

        if message.lower() == 'exit':
            ack_checksum = cal_checksum("ACK")
            packet = f"ACK:{ack_checksum}:{seq_no}"
            receiver_socket.sendto(packet.encode(), sender_address)
            print(f"Connection terminated by sender {sender_address}.")
            break

        ack_checksum = cal_checksum("ACK")
        packet = f"ACK:{ack_checksum}:{seq_no}"
        if random.random() >= LOSS_PROBABILITY:
            if random.random() < CORRUPT_PROBABILITY:
                bad_checksum = cal_checksum("CORRUPTED")
                packet = f"ACK:{bad_checksum}:{seq_no}"
                print(f"ACK {seq_no} corrupted before sending.")
            receiver_socket.sendto(packet.encode(), sender_address)
            expected_seq += 1
        else:
            print(f"ACK {seq_no} lost (simulated). Sender will retransmit.")

    except KeyboardInterrupt:
        print("Receiver interrupted.")
        break

receiver_socket.close()
