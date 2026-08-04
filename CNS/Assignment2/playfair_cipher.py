import re

ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ"

def build_key_square(keyword):
    keyword = keyword.upper().replace("J", "I")
    seen = []
    for ch in keyword:
        if ch.isalpha() and ch not in seen:
            seen.append(ch)
    for ch in ALPHABET:
        if ch not in seen:
            seen.append(ch)
    return seen

def grid_position(square, letter):
    idx = square.index(letter)
    return idx // 5, idx % 5

def prepare_plaintext(text):
    text = re.sub(r"[^A-Za-z]", "", text).upper().replace("J", "I")
    pairs = []
    i = 0
    while i < len(text):
        a = text[i]
        b = text[i + 1] if i + 1 < len(text) else "X"
        if a == b:
            pairs.append(a + "X")
            i += 1
        else:
            pairs.append(a + b)
            i += 2
    if len(pairs[-1]) == 1:
        pairs[-1] += "X"
    return pairs

def encrypt(plaintext, keyword):
    square = build_key_square(keyword)
    pairs = prepare_plaintext(plaintext)
    cipher = ""
    for a, b in pairs:
        ra, ca = grid_position(square, a)
        rb, cb = grid_position(square, b)
        if ra == rb:  # same row -> shift right
            cipher += square[ra * 5 + (ca + 1) % 5]
            cipher += square[rb * 5 + (cb + 1) % 5]
        elif ca == cb:  # same column -> shift down
            cipher += square[((ra + 1) % 5) * 5 + ca]
            cipher += square[((rb + 1) % 5) * 5 + cb]
        else:  # rectangle -> swap columns
            cipher += square[ra * 5 + cb]
            cipher += square[rb * 5 + ca]
    return cipher

def decrypt(ciphertext, keyword):
    square = build_key_square(keyword)
    return decrypt_with_square(ciphertext, square)

def decrypt_with_square(ciphertext, square):
    text = re.sub(r"[^A-Za-z]", "", ciphertext).upper()
    plain = ""
    for i in range(0, len(text) - 1, 2):
        a, b = text[i], text[i + 1]
        ra, ca = grid_position(square, a)
        rb, cb = grid_position(square, b)
        if ra == rb:
            plain += square[ra * 5 + (ca - 1) % 5]
            plain += square[rb * 5 + (cb - 1) % 5]
        elif ca == cb:
            plain += square[((ra - 1) % 5) * 5 + ca]
            plain += square[((rb - 1) % 5) * 5 + cb]
        else:
            plain += square[ra * 5 + cb]
            plain += square[rb * 5 + ca]
    return plain


CANDIDATE_KEYWORDS = [
    "MONARCHY", "PLAYFAIR", "KEYWORD", "SECURITY", "CRYPTOGRAPHY",
    "COMPUTER", "NETWORK", "ENCRYPT", "PASSWORD", "GOVERNMENT",
    "HISTORY", "SCIENCE", "FREEDOM", "JUSTICE", "MESSAGE",
    "SECRET", "CIPHER", "ALGORITHM", "UNIVERSITY", "LANGUAGE",
    "MATHEMATICS", "ENGINEERING", "INFORMATION", "COMMUNICATION",
    "PROTOCOL", "DEFENSE", "STRATEGY", "AUTHORITY", "REPUBLIC",
    "DIAMOND", "ELEPHANT", "MOUNTAIN", "TREASURE", "CASTLE",
    "GARDEN", "LIBRARY", "MIDNIGHT", "SHADOW", "THUNDER",
]

COMMON_DIGRAMS = {
    "TH": 3.56, "HE": 3.07, "IN": 2.43, "ER": 2.05, "AN": 1.99,
    "RE": 1.85, "ON": 1.76, "AT": 1.49, "EN": 1.45, "ND": 1.35,
    "TI": 1.34, "ES": 1.34, "OR": 1.28, "TE": 1.20, "OF": 1.17,
    "ED": 1.17, "IS": 1.13, "IT": 1.12, "AL": 1.09, "AR": 1.07,
    "ST": 1.05, "TO": 1.04, "NT": 1.04, "NG": 0.95, "SE": 0.93,
    "HA": 0.93, "AS": 0.87, "OU": 0.87, "IO": 0.83, "LE": 0.83,
    "VE": 0.83, "CO": 0.79, "ME": 0.79, "DE": 0.76, "HI": 0.76,
    "RI": 0.73, "RO": 0.73, "IC": 0.70, "NE": 0.69, "EA": 0.69,
    "RA": 0.69, "CE": 0.65, "LI": 0.62, "CH": 0.60, "LL": 0.58,
    "BE": 0.58, "MA": 0.56, "SI": 0.55, "OM": 0.55, "UR": 0.54,
    "CA": 0.52, "EL": 0.51, "TA": 0.50, "LA": 0.49, "NS": 0.49,
    "DI": 0.48, "FO": 0.48, "HO": 0.48, "PE": 0.47, "EC": 0.46,
    "PR": 0.45, "NO": 0.45, "CT": 0.43, "US": 0.43, "AC": 0.42,
    "OT": 0.42, "IL": 0.42, "TR": 0.42, "LY": 0.41, "NC": 0.40,
    "WA": 0.40, "EM": 0.39, "WI": 0.39, "WH": 0.39, "PA": 0.37,
    "HT": 0.37, "EE": 0.37, "GE": 0.37, "SO": 0.37, "OW": 0.36,
    "EV": 0.35, "UN": 0.35, "UT": 0.35, "SA": 0.34, "AD": 0.34,
    "AM": 0.34, "GA": 0.33, "TS": 0.33, "EI": 0.32, "NI": 0.32,
    "MO": 0.32, "ID": 0.31, "GH": 0.31, "AB": 0.31, "NA": 0.30,
    "SU": 0.30, "PI": 0.29, "OP": 0.29, "SH": 0.29, "KE": 0.29,
    "OL": 0.29, "IF": 0.28, "IE": 0.28, "AY": 0.28, "WO": 0.28,
}

def score_text(text):
    score = 0.0
    for i in range(len(text) - 1):
        pair = text[i:i + 2]
        score += COMMON_DIGRAMS.get(pair, 0.01)
    return score

def dictionary_attack(ciphertext, wordlist=CANDIDATE_KEYWORDS):
    results = []
    for word in wordlist:
        candidate_plain = decrypt(ciphertext, word)
        candidate_score = score_text(candidate_plain)
        results.append((word, candidate_plain, candidate_score))

    results.sort(key=lambda r: r[2], reverse=True)
    return results

if __name__ == "__main__":
    keyword = "MONARCHY"
    plaintext = ("MEET ME AT THE HIDDEN GARDEN BEHIND THE OLD LIBRARY "
                 "AFTER MIDNIGHT AND BRING THE SEALED ENVELOPE WITH YOU")

    print("PLAYFAIR CIPHER - ENCRYPTION")
    print("Keyword   :", keyword)
    print("Plaintext :", plaintext)

    ciphertext = encrypt(plaintext, keyword)
    print("Ciphertext:", ciphertext)

    decrypted = decrypt(ciphertext, keyword)
    print("Decrypted (with correct key):", decrypted)

    print()
    print("CRYPTANALYSIS")
    print("Attacking ciphertext:", ciphertext)

    ranked = dictionary_attack(ciphertext)

    print()
    print("Top 3 guesses (keyword : fitness score : decrypted text):")
    for word, text, sc in ranked[:3]:
        print(f"  {word:12s} {sc:7.2f}  {text}")

    best_word, best_text, best_score = ranked[0]
    print()
    print("Recovered keyword :", best_word)
    print("Recovered plaintext:", best_text)
