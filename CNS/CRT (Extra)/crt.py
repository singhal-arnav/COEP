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


def crt(remainders, moduli):
    n = len(moduli)

    for i in range(n):
        for j in range(i + 1, n):
            g, _, _ = extended_gcd(moduli[i], moduli[j])
            if g != 1:
                raise ValueError(
                    f"moduli {moduli[i]} and {moduli[j]} are not pairwise coprime"
                )

    M = 1
    for m in moduli:
        M *= m

    x = 0
    for r, m in zip(remainders, moduli):
        Mi = M // m
        Mi_inv = mod_inverse(Mi % m, m)
        x += r * Mi * Mi_inv

    return x % M, M


def read_congruences():
    n = int(input("Enter the number of congruences: "))
    remainders = []
    moduli = []
    for i in range(n):
        r = int(input(f"Enter remainder a{i + 1} (x = a{i + 1} mod n{i + 1}): "))
        m = int(input(f"Enter modulus n{i + 1}: "))
        remainders.append(r)
        moduli.append(m)
    return remainders, moduli


def main():
    remainders, moduli = read_congruences()
    try:
        x, M = crt(remainders, moduli)
    except ValueError as e:
        print("Error:", e)
        return

    print()
    print("System of congruences:")
    for r, m in zip(remainders, moduli):
        print(f"  x = {r} (mod {m})")

    print()
    print(f"Solution: x = {x} (mod {M})")

    print()
    print("Verification:")
    for r, m in zip(remainders, moduli):
        print(f"  {x} mod {m} = {x % m}  (expected {r})")


if __name__ == "__main__":
    main()
