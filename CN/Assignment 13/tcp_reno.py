import random

def simulate_tcp_reno(total_packets, ssthresh, max_cwnd, loss_probability):
    cwnd = 1
    packets_sent = 0
    packets_lost = 0
    total_acks = 0
    retransmissions = 0
    packets_status = {i: False for i in range(1, total_packets + 1)}

    while packets_sent < total_packets:
        packets_to_send = min(cwnd, total_packets - packets_sent)
        current_window = list(range(packets_sent + 1, packets_sent + packets_to_send + 1))
        print(f"\nSending packets: {current_window} (cwnd={cwnd}, ssthresh={ssthresh})")

        lost_packets = []
        acked_count = 0

        for packet in current_window:
            if random.random() < loss_probability:
                lost_packets.append(packet)
                packets_lost += 1
                print(f"  Packet {packet} lost.")
            else:
                packets_status[packet] = True
                total_acks += 1
                acked_count += 1
                print(f"  Packet {packet} acknowledged.")

        if lost_packets:
            first_lost = lost_packets[0]
            dup_acks = acked_count

            if dup_acks >= 3:
                print(f"\n  3 duplicate ACKs detected. Fast Retransmit for packet {first_lost}.")
                retransmissions += 1
                packets_status[first_lost] = True
                total_acks += 1
                print(f"  Packet {first_lost} acknowledged after fast retransmit.")

                ssthresh = max(cwnd // 2, 1)
                cwnd = ssthresh + 3
                print(f"  Fast Recovery: ssthresh={ssthresh}, cwnd={cwnd}.")

                for extra in lost_packets[1:]:
                    retransmissions += 1
                    packets_status[extra] = True
                    total_acks += 1
                    cwnd += 1
                    print(f"  Retransmitting packet {extra} in fast recovery. cwnd={cwnd}.")

                cwnd = ssthresh
                cwnd = min(cwnd, max_cwnd)
                print(f"  Fast Recovery ends. cwnd={cwnd}.")
            else:
                for packet in lost_packets:
                    retransmissions += 1
                    packets_status[packet] = True
                    total_acks += 1
                    print(f"  Timeout retransmit for packet {packet}.")

                ssthresh = max(cwnd // 2, 1)
                cwnd = 1
                print(f"  Timeout: ssthresh={ssthresh}, cwnd reset to 1 (Slow Start).")
        else:
            if cwnd < ssthresh:
                cwnd = min(cwnd * 2, ssthresh)
            else:
                cwnd += 1
            cwnd = min(cwnd, max_cwnd)

        for packet in current_window:
            if packets_status[packet]:
                packets_sent += 1

    print(f"\nTCP Reno done. ACKs: {total_acks}, Packets lost: {packets_lost}, Retransmissions: {retransmissions}")

total_packets = int(input("Enter the total number of packets: "))
ssthresh = int(input("Enter initial ssthresh: "))
max_cwnd = int(input("Enter max cwnd: "))
loss_probability = float(input("Enter the packet loss probability (0 to 1): "))
simulate_tcp_reno(total_packets, ssthresh, max_cwnd, loss_probability)
