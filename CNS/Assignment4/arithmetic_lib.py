import random


def mod_exp(base, exp, mod):
    if mod == 1:
        return 0
    result = 1
    base = base % mod
    while exp > 0:
        if exp & 1:
            result = (result * base) % mod
        exp >>= 1
        base = (base * base) % mod
    return result


def gcd(a, b):
    a, b = abs(a), abs(b)
    while b != 0:
        a, b = b, a % b
    return a


def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return g, x, y


def mod_inverse(a, m):
    g, x, _ = extended_gcd(a, m)
    if g != 1:
        return None
    return x % m


def euler_phi(n):
    result = n
    p = 2
    temp = n
    while p * p <= temp:
        if temp % p == 0:
            while temp % p == 0:
                temp //= p
            result -= result // p
        p += 1
    if temp > 1:
        result -= result // temp
    return result


def prime_factors(n):
    factors = []
    temp = n
    p = 2
    while p * p <= temp:
        if temp % p == 0:
            factors.append(p)
            while temp % p == 0:
                temp //= p
        p += 1
    if temp > 1:
        factors.append(temp)
    return factors


def has_primitive_root(n):
    if n in (1, 2, 4):
        return True
    if n % 2 == 0:
        n //= 2
    if n % 2 == 0:
        return False
    factors = prime_factors(n)
    return len(factors) == 1


def primitive_roots(n):
    if not has_primitive_root(n):
        return []
    phi = euler_phi(n)
    phi_factors = prime_factors(phi)
    roots = []
    for g in range(2, n):
        if gcd(g, n) != 1:
            continue
        is_root = True
        for q in phi_factors:
            if mod_exp(g, phi // q, n) == 1:
                is_root = False
                break
        if is_root:
            roots.append(g)
    return roots


def miller_rabin(n, k=20):
    if n in (2, 3):
        return True
    if n < 2 or n % 2 == 0:
        return False

    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = mod_exp(a, d, n)
        if x == 1 or x == n - 1:
            continue
        composite = True
        for _ in range(r - 1):
            x = (x * x) % n
            if x == n - 1:
                composite = False
                break
        if composite:
            return False
    return True


GF_MOD = 0b100011011


def gf_add(a, b):
    return a ^ b


def gf_mult(a, b):
    result = 0
    x = a
    y = b
    for _ in range(8):
        if y & 1:
            result ^= x
        carry = x & 0x80
        x <<= 1
        if carry:
            x ^= GF_MOD
        x &= 0xFF
        y >>= 1
    return result & 0xFF


def gf_pow(a, exp):
    result = 1
    base = a
    while exp > 0:
        if exp & 1:
            result = gf_mult(result, base)
        base = gf_mult(base, base)
        exp >>= 1
    return result


def gf_inverse(a):
    if a == 0:
        return 0
    return gf_pow(a, 254)


def poly_to_str(a):
    if a == 0:
        return "0"
    terms = []
    for i in range(7, -1, -1):
        if a & (1 << i):
            if i == 0:
                terms.append("1")
            elif i == 1:
                terms.append("x")
            else:
                terms.append(f"x^{i}")
    return " + ".join(terms)


def read_int(prompt):
    while True:
        raw = input(prompt).strip()
        try:
            return int(raw)
        except ValueError:
            print("Please enter a valid integer.")


def read_gf_byte(prompt):
    while True:
        raw = input(prompt).strip()
        try:
            if raw.lower().startswith("0x"):
                value = int(raw, 16)
            else:
                value = int(raw)
        except ValueError:
            print("Please enter a valid byte, as decimal or hex (e.g. 0x57).")
            continue
        if 0 <= value <= 255:
            return value
        print("Value must be between 0 and 255 (a single byte).")


def menu_mod_exp():
    base = read_int("Enter base a: ")
    exp = read_int("Enter exponent b: ")
    mod = read_int("Enter modulus n: ")
    print(f"{base}^{exp} mod {mod} = {mod_exp(base, exp, mod)}")


def menu_gcd():
    a = read_int("Enter first number a: ")
    b = read_int("Enter second number b: ")
    print(f"gcd({a}, {b}) = {gcd(a, b)}")


def menu_mod_inverse():
    a = read_int("Enter number a: ")
    m = read_int("Enter modulus m: ")
    inv = mod_inverse(a, m)
    if inv is None:
        print(f"No modular inverse exists for {a} mod {m} since gcd({a}, {m}) != 1")
    else:
        print(f"Inverse of {a} mod {m} = {inv}")
        print(f"Check: ({a} * {inv}) mod {m} = {(a * inv) % m}")


def menu_primitive_roots():
    n = read_int("Enter n: ")
    if n < 1:
        print("n must be a positive integer.")
        return
    roots = primitive_roots(n)
    if not roots:
        print(f"{n} has no primitive roots.")
    else:
        print(f"Primitive roots of {n}: {roots}")


def menu_miller_rabin():
    n = read_int("Enter the number to test: ")
    k = read_int("Enter the number of rounds (e.g. 20): ")
    if k < 1:
        print("Number of rounds must be at least 1.")
        return
    result = miller_rabin(n, k)
    print(f"{n} is prime: {result}")


def menu_gf():
    print("1. Addition (XOR)")
    print("2. Multiplication")
    print("3. Multiplicative Inverse")
    choice = read_int("Choose an operation: ")
    if choice == 1:
        a = read_gf_byte("Enter byte a (decimal or hex, e.g. 0x57): ")
        b = read_gf_byte("Enter byte b (decimal or hex, e.g. 0x83): ")
        result = gf_add(a, b)
        print(f"a = 0x{a:02X} ({poly_to_str(a)})")
        print(f"b = 0x{b:02X} ({poly_to_str(b)})")
        print(f"a + b = 0x{result:02X} ({poly_to_str(result)})")
    elif choice == 2:
        a = read_gf_byte("Enter byte a (decimal or hex, e.g. 0x57): ")
        b = read_gf_byte("Enter byte b (decimal or hex, e.g. 0x83): ")
        result = gf_mult(a, b)
        print(f"a = 0x{a:02X} ({poly_to_str(a)})")
        print(f"b = 0x{b:02X} ({poly_to_str(b)})")
        print(f"a * b = 0x{result:02X} ({poly_to_str(result)})")
    elif choice == 3:
        a = read_gf_byte("Enter byte a (decimal or hex, e.g. 0x57): ")
        inv = gf_inverse(a)
        print(f"a = 0x{a:02X} ({poly_to_str(a)})")
        print(f"inverse of a = 0x{inv:02X} ({poly_to_str(inv)})")
        print(f"check: (a * inverse of a) = 0x{gf_mult(a, inv):02X}")
    else:
        print("Invalid choice.")


def print_menu():
    print()
    print("Arithmetic Function Library")
    print("1. Modular Exponentiation (a^b mod n)")
    print("2. Euclidean Algorithm for GCD")
    print("3. Extended Euclidean Algorithm for Modular Inverse")
    print("4. Primitive Roots of a Number")
    print("5. Miller-Rabin Primality Test")
    print("6. Polynomial Arithmetic on GF(2^8)")
    print("7. Exit")


def main():
    while True:
        print_menu()
        choice = read_int("Enter your choice: ")
        print()
        if choice == 1:
            menu_mod_exp()
        elif choice == 2:
            menu_gcd()
        elif choice == 3:
            menu_mod_inverse()
        elif choice == 4:
            menu_primitive_roots()
        elif choice == 5:
            menu_miller_rabin()
        elif choice == 6:
            menu_gf()
        elif choice == 7:
            print("Exiting.")
            break
        else:
            print("Invalid choice, please select an option from the menu.")


if __name__ == "__main__":
    main()
