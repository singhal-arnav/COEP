import socket
import struct
import random

ROOT_SERVERS = ["198.41.0.4"]
CACHE = {}

def build_query(domain):
    packet_id = random.randint(0, 65535)
    header = struct.pack("!HHHHHH", packet_id, 0x0000, 1, 0, 0, 0)
    qname = b""
    for part in domain.split("."):
        qname += struct.pack("B", len(part)) + part.encode()
    qname += b"\x00"
    question = qname + struct.pack("!HH", 1, 1)
    return header + question

def parse_name(data, offset):
    labels = []
    while True:
        length = data[offset]
        if length & 0xC0 == 0xC0:
            pointer = struct.unpack("!H", data[offset:offset+2])[0] & 0x3FFF
            name, _ = parse_name(data, pointer)
            labels.append(name)
            return ".".join(labels), offset + 2
        offset += 1
        if length == 0: break
        labels.append(data[offset:offset+length].decode())
        offset += length
    return ".".join(labels), offset

def send_query(query, server):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(3.0)
    try:
        sock.sendto(query, (server, 53))
        data, _ = sock.recvfrom(1024)
        return data
    except: return None
    finally: sock.close()

def resolve_iteratively(domain):
    if domain in CACHE: return CACHE[domain]
    
    # Ensure domain ends with a dot for consistent matching
    search_domain = domain if domain.endswith('.') else domain + '.'
    current_server = ROOT_SERVERS[0]
    
    while True:
        print(f"Querying {current_server} for {search_domain}...")
        query = build_query(domain) # build_query handles the dot internally
        response = send_query(query, current_server)
        
        if not response: return None

        _, _, qd, an, ns, ar = struct.unpack("!HHHHHH", response[:12])
        offset = 12
        for _ in range(qd):
            _, offset = parse_name(response, offset)
            offset += 4

        # 1. Check Answer Section for A or CNAME
        for _ in range(an):
            name, offset = parse_name(response, offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[offset:offset+10])
            offset += 10
            if rtype == 1: # A Record
                ip = socket.inet_ntoa(response[offset:offset+4])
                CACHE[domain] = ip
                return ip
            elif rtype == 5: # CNAME Record
                cname, _ = parse_name(response, offset)
                print(f"Followed CNAME to {cname}")
                return resolve_iteratively(cname) # Restart for the new name
            offset += rdlen

        # 2. Extract Authority (NS names) and Additional (Glue IPs)
        ns_names = []
        auth_offset = offset
        for _ in range(ns):
            _, auth_offset = parse_name(response, auth_offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[auth_offset:auth_offset+10])
            auth_offset += 10
            if rtype == 2: # NS Record
                ns_name, _ = parse_name(response, auth_offset)
                ns_names.append(ns_name)
            auth_offset += rdlen

        glue_ips = {}
        add_offset = auth_offset
        for _ in range(ar):
            name, add_offset = parse_name(response, add_offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[add_offset:add_offset+10])
            add_offset += 10
            if rtype == 1: # A Record
                glue_ips[name] = socket.inet_ntoa(response[add_offset:add_offset+4])
            add_offset += rdlen

        # 3. Decide next hop
        next_server = None
        for name in ns_names:
            if name in glue_ips:
                next_server = glue_ips[name]
                break
        
        # If no glue record, resolve the NS name itself!
        if not next_server and ns_names:
            print(f"No glue record for {ns_names[0]}, resolving NS first...")
            next_server = resolve_iteratively(ns_names[0])

        if next_server:
            current_server = next_server
        else:
            return None

if __name__ == "__main__":
    target = input("Enter the domain you want to resolve: ")
    ip_result = resolve_iteratively(target)
    if ip_result:
        print(f"IP address for {target}: {ip_result}")
    else:
        print("Could not resolve domain.")
