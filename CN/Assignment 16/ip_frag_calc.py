import sys

def fragment_packet(packet_size, mtu, header_size=20, level=1, base_offset=0, parent_mf=0):
    if packet_size <= mtu:
        print(f"  No fragmentation needed (packet {packet_size}B <= MTU {mtu}B)")
        return []

    max_data = mtu - header_size
    aligned_data = (max_data // 8) * 8
    if aligned_data <= 0:
        print(f"  MTU too small to carry any data after header.")
        return []

    total_data = packet_size - header_size
    fragments = []
    offset = base_offset

    print(f"\nLevel {level} fragmentation  (packet={packet_size}B, MTU={mtu}B, max data/fragment={aligned_data}B):")
    print(f"  {'Frag':<6} {'Header':>8} {'Data':>8} {'Offset (bytes)':>16} {'Offset (8B units)':>18} {'MF flag':>8} {'Total size':>11}")
    print(f"  {'-'*6} {'-'*8} {'-'*8} {'-'*16} {'-'*18} {'-'*8} {'-'*11}")

    frag_num = 1
    remaining = total_data

    while remaining > 0:
        data_in_frag = min(aligned_data, remaining)
        is_last = (remaining - data_in_frag) == 0
        if not is_last:
            data_in_frag = (data_in_frag // 8) * 8
        mf = (0 if is_last else 1) if parent_mf == 0 else 1
        total_frag_size = header_size + data_in_frag
        print(f"  {frag_num:<6} {header_size:>8} {data_in_frag:>8} {offset:>16} {offset // 8:>18} {mf:>8} {total_frag_size:>11}")
        fragments.append((total_frag_size, offset, mf))
        offset += data_in_frag
        remaining -= data_in_frag
        frag_num += 1

    return fragments


packet_size = int(input("Enter the original packet size (including header, in bytes): "))
header_size_input = input("Enter header size in bytes (press Enter for default 20): ").strip()
header_size = int(header_size_input) if header_size_input else 20
initial_mtu = int(input("Enter the MTU size for Level 1: "))

print(f"\nOriginal packet: {packet_size}B  Header: {header_size}B  Data: {packet_size - header_size}B")

fragments = fragment_packet(packet_size, initial_mtu, header_size, level=1, base_offset=0, parent_mf=0)

if not fragments:
    sys.exit(1)

level = 1
while fragments:
    next_mtu_input = input("\nEnter MTU to fragment further (or -23 to stop): ").strip()
    next_mtu = int(next_mtu_input)
    if next_mtu == -23:
        break
    level += 1
    new_fragments = []
    for (frag_total_size, frag_offset, frag_mf) in fragments:
        result = fragment_packet(frag_total_size, next_mtu, header_size, level, base_offset=frag_offset, parent_mf=frag_mf)
        new_fragments.extend(result)
    if not new_fragments:
        print("No further fragmentation occurred.")
        break
    fragments = new_fragments

print("\nFragmentation complete.")
