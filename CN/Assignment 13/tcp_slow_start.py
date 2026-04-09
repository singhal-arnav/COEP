import random

def tcp_slow_start(initial_cwnd, ssthresh, max_cwnd, loss_probability, max_iterations):
    cwnd = initial_cwnd
    iteration = 0

    while iteration < max_iterations:
        print(f"Iteration {iteration}: cwnd={cwnd} (Slow Start)")

        if cwnd >= ssthresh:
            print(f"Slow Start phase ends at iteration {iteration}. cwnd={cwnd} reached ssthresh={ssthresh}.")
            break

        if random.random() < loss_probability:
            print(f"  Packet loss detected at cwnd={cwnd}!")
            ssthresh = max(cwnd // 2, 1)
            cwnd = 1
            print(f"  ssthresh={ssthresh}, cwnd reset to 1 (Slow Start).")
        else:
            cwnd *= 2
            if cwnd > ssthresh:
                cwnd = ssthresh
            cwnd = min(cwnd, max_cwnd)

        iteration += 1

    print(f"\nFinal cwnd={cwnd}, ssthresh={ssthresh}")

initial_cwnd = int(input("Enter initial congestion window size: "))
ssthresh = int(input("Enter initial ssthresh: "))
max_cwnd = int(input("Enter max cwnd: "))
loss_probability = float(input("Enter the packet loss probability (0 to 1): "))
max_iterations = int(input("Enter max number of iterations: "))
tcp_slow_start(initial_cwnd, ssthresh, max_cwnd, loss_probability, max_iterations)
