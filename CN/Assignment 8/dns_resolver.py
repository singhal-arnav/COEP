import socket
import struct
import random
import time
import os

ROOT_SERVERS = [
    "198.41.0.4",      # a.root-servers.net
    "170.9.1.1",       # b.root-servers.net
    "192.33.4.12",     # c.root-servers.net
    "199.7.91.13",     # d.root-servers.net
    "192.203.230.10",  # e.root-servers.net
    "192.5.5.241",     # f.root-servers.net
    "192.112.36.4",    # g.root-servers.net
    "198.97.190.53",   # h.root-servers.net
    "192.36.148.17",   # i.root-servers.net
    "192.58.128.30",   # j.root-servers.net
    "193.0.14.129",    # k.root-servers.net
    "199.7.83.42",     # l.root-servers.net
    "202.12.27.33",    # m.root-servers.net
]

CACHE: dict[str, tuple[str, float]] = {}

HOSTS_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "dns_hosts.txt")


def load_hosts() -> dict[str, str]:
    """Return {domain: ip} from our custom hosts file (comments with # ignored)."""
    entries: dict[str, str] = {}
    if not os.path.exists(HOSTS_FILE):
        return entries
    with open(HOSTS_FILE) as fh:
        for line in fh:
            line = line.split("#")[0].strip()
            if not line:
                continue
            parts = line.split()
            if len(parts) >= 2:
                ip, *domains = parts
                for domain in domains:
                    entries[domain.lower()] = ip
    return entries


def save_hosts(entries: dict[str, str]) -> None:
    """Write the in-memory hosts dict back to disk."""
    with open(HOSTS_FILE, "w") as fh:
        fh.write("# Custom hosts file managed by dns_resolver.py\n")
        fh.write("# Format: <ip>  <domain> [<domain> ...]\n\n")
        for domain, ip in sorted(entries.items()):
            fh.write(f"{ip}\t{domain}\n")


def add_host_entry(domain: str, ip: str) -> None:
    """Add or update a static entry in the hosts file."""
    entries = load_hosts()
    entries[domain.lower()] = ip
    save_hosts(entries)
    print(f"[hosts] Saved: {domain} -> {ip}")


def remove_host_entry(domain: str) -> bool:
    """Remove a domain from the hosts file. Returns True if it existed."""
    entries = load_hosts()
    domain = domain.lower()
    if domain in entries:
        del entries[domain]
        save_hosts(entries)
        print(f"[hosts] Removed: {domain}")
        return True
    print(f"[hosts] Not found: {domain}")
    return False


def list_hosts() -> None:
    """Print all entries currently in the hosts file."""
    entries = load_hosts()
    if not entries:
        print("[hosts] (empty)")
        return
    width = max(len(d) for d in entries)
    for domain, ip in sorted(entries.items()):
        print(f"  {domain:<{width}}  ->  {ip}")

def cache_get(domain: str) -> str | None:
    """Return cached IP for domain if still valid, else None."""
    entry = CACHE.get(domain)
    if entry is None:
        return None
    ip, expiry = entry
    if time.time() < expiry:
        remaining = int(expiry - time.time())
        print(f"[cache] Hit for {domain} -> {ip}  (TTL {remaining}s remaining)")
        return ip
    del CACHE[domain]
    print(f"[cache] Expired entry for {domain}")
    return None


def cache_set(domain: str, ip: str, ttl: int) -> None:
    """Store an IP in the cache with an absolute expiry timestamp."""
    expiry = time.time() + ttl
    CACHE[domain] = (ip, expiry)
    print(f"[cache] Stored {domain} -> {ip}  (TTL {ttl}s)")

def build_query(domain: str) -> tuple[bytes, int]:
    packet_id = random.randint(0, 65535)
    header = struct.pack("!HHHHHH", packet_id, 0x0000, 1, 0, 0, 0)
    qname = b""
    for part in domain.split("."):
        qname += struct.pack("B", len(part)) + part.encode()
    qname += b"\x00"
    question = qname + struct.pack("!HH", 1, 1)
    return header + question, packet_id


def parse_name(data: bytes, offset: int) -> tuple[str, int]:
    labels = []
    while True:
        length = data[offset]
        if length & 0xC0 == 0xC0:
            pointer = struct.unpack("!H", data[offset:offset + 2])[0] & 0x3FFF
            name, _ = parse_name(data, pointer)
            labels.append(name)
            return ".".join(labels), offset + 2
        offset += 1
        if length == 0:
            break
        labels.append(data[offset:offset + length].decode())
        offset += length
    return ".".join(labels), offset


def send_query(query: bytes, server: str, expected_id: int) -> bytes | None:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(3.0)
    try:
        sock.sendto(query, (server, 53))
        for _ in range(3):
            data, _ = sock.recvfrom(4096)
            if struct.unpack("!H", data[:2])[0] == expected_id:
                return data
        return None
    except Exception:
        return None
    finally:
        sock.close()

def resolve_iteratively(domain: str, depth: int = 0) -> str | None:
    domain = domain.lower().rstrip(".")

    if depth > 10:
        print("Error: Too many redirections")
        return None

    hosts = load_hosts()
    if domain in hosts:
        print(f"[hosts] Match: {domain} -> {hosts[domain]}")
        return hosts[domain]

    cached = cache_get(domain)
    if cached:
        return cached

    current_server = random.choice(ROOT_SERVERS)

    while True:
        print(f"Querying {current_server} for {domain}...")
        query, packet_id = build_query(domain)
        response = send_query(query, current_server, packet_id)

        if not response:
            print(f"No response from {current_server}")
            return None

        _, flags, qd, an, ns, ar = struct.unpack("!HHHHHH", response[:12])
        rcode = flags & 0x000F

        if rcode == 3:
            print(f"NXDOMAIN: {domain} does not exist")
            return None

        offset = 12

        for _ in range(qd):
            _, offset = parse_name(response, offset)
            offset += 4

        for _ in range(an):
            name, offset = parse_name(response, offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[offset:offset + 10])
            offset += 10
            if rtype == 1 and rdlen == 4:           
                ip = socket.inet_ntoa(response[offset:offset + 4])
                cache_set(domain, ip, ttl)
                offset += rdlen
                return ip
            elif rtype == 5:                         
                cname, _ = parse_name(response, offset)
                print(f"Followed CNAME: {domain} -> {cname}")
                offset += rdlen
                return resolve_iteratively(cname, depth + 1)
            offset += rdlen

        ns_names: list[str] = []
        auth_offset = offset
        for _ in range(ns):
            _, auth_offset = parse_name(response, auth_offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[auth_offset:auth_offset + 10])
            auth_offset += 10
            if rtype == 2:
                ns_name, _ = parse_name(response, auth_offset)
                ns_names.append(ns_name)
            auth_offset += rdlen

        glue_ips: dict[str, str] = {}
        add_offset = auth_offset
        for _ in range(ar):
            name, add_offset = parse_name(response, add_offset)
            rtype, rclass, ttl, rdlen = struct.unpack("!HHIH", response[add_offset:add_offset + 10])
            add_offset += 10
            if rtype == 1 and rdlen == 4:
                glue_ips[name] = socket.inet_ntoa(response[add_offset:add_offset + 4])
            add_offset += rdlen

        next_server = None
        for name in ns_names:
            if name in glue_ips:
                next_server = glue_ips[name]
                break

        if not next_server and ns_names:
            print(f"No glue for {ns_names[0]}, resolving NS name first...")
            next_server = resolve_iteratively(ns_names[0], depth + 1)

        if next_server:
            current_server = next_server
        else:
            print("Could not determine next nameserver")
            return None

def print_help() -> None:
    print("""
DNS Resolver — commands
  resolve <domain>              Resolve a domain to its IP address
  hosts list                    List all custom hosts file entries
  hosts add <domain> <ip>       Add / update a static hosts entry
  hosts remove <domain>         Remove a static hosts entry
  cache clear                   Clear the in-memory TTL cache
  help                          Show this message
  exit / quit                   Exit
""")


if __name__ == "__main__":
    print("DNS Resolver  (type 'help' for commands)\n")
    while True:
        try:
            raw = input("> ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nExiting...")
            break

        if not raw:
            continue

        parts = raw.split()
        cmd = parts[0].lower()

        if cmd in ("exit", "quit"):
            print("Exiting...")
            break

        elif cmd == "help":
            print_help()

        elif cmd == "resolve":
            if len(parts) < 2:
                print("Usage: resolve <domain>")
            else:
                domain = parts[1]
                ip = resolve_iteratively(domain)
                if ip:
                    print(f"\nResult: {domain} -> {ip}\n")
                else:
                    print(f"\nCould not resolve {domain}\n")

        elif cmd == "hosts":
            if len(parts) < 2:
                print("Usage: hosts list | hosts add <domain> <ip> | hosts remove <domain>")
            else:
                sub = parts[1].lower()
                if sub == "list":
                    list_hosts()
                elif sub == "add":
                    if len(parts) != 4:
                        print("Usage: hosts add <domain> <ip>")
                    else:
                        add_host_entry(parts[2], parts[3])
                elif sub == "remove":
                    if len(parts) != 3:
                        print("Usage: hosts remove <domain>")
                    else:
                        remove_host_entry(parts[2])
                else:
                    print("Unknown hosts sub-command. Use: list / add / remove")

        elif cmd == "cache":
            if len(parts) >= 2 and parts[1].lower() == "clear":
                CACHE.clear()
                print("[cache] Cleared.")
            else:
                print("Usage: cache clear")

        else:
            ip = resolve_iteratively(parts[0])
            if ip:
                print(f"\nResult: {parts[0]} -> {ip}\n")
            else:
                print(f"\nCould not resolve {parts[0]}\n")
