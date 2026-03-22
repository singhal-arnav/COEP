c = input("Select the class (A, B, C): ")

if c == 'A':
    csm = 8
elif c == 'B':
    csm = 16
elif c == 'C':
    csm = 24
else:
    print("Invalid class")
    exit()

print("Subnet mask of class {}: /{}".format(c, csm))

b = input("Enter the subnet mask (/ notation): ")
sm = int(b[1:])
if sm < csm:
    print("Invalid subnet mask: c   annot be less than /{} for Class {}".format(csm, c))
    exit()

a = input("Enter the IP address: ")

octets = list(map(int, a.split('.')))

mask = []
temp = sm
for i in range(4):
    if temp >= 8:
        mask.append(255)
        temp -= 8
    else:
        if temp > 0:
            mask.append(256 - (2 ** (8 - temp)))
        else:
            mask.append(0)
        temp = 0

print("\nSubnet Mask:", ".".join(map(str, mask)))

subnets = 2 ** (sm - csm)
hosts_per_subnet = (2 ** (32 - sm)) - 2

print("Number of subnets =", subnets)
print("Number of hosts per subnet =", hosts_per_subnet)
print()

ip_int = 0
mask_int = 0
for i in range(4):
    ip_int = (ip_int << 8) | octets[i]
    mask_int = (mask_int << 8) | mask[i]

inv_mask = (~mask_int) & 0xFFFFFFFF

block_size = 2 ** (32 - sm)

for i in range(subnets):
    print("Subnet", i + 1)

    network = (ip_int & mask_int) + i * block_size

    broadcast = network | inv_mask

    first_host = network + 1
    last_host = broadcast - 1

    def to_ip(n):
        return ".".join(str((n >> (8 * j)) & 255) for j in reversed(range(4)))

    print("Network ID:", to_ip(network))
    print("Broadcast Address:", to_ip(broadcast))
    print("Valid Host Range:", to_ip(first_host), "to", to_ip(last_host))
    print()
