import random
import string

alphabet = string.ascii_lowercase

def caesar_cipher(plaintext, key):
    ciphertext = ""
    for c in plaintext:
        if c not in alphabet:
            ciphertext += c
            continue
        ciphertext += alphabet[(alphabet.index(c) + key) % len(alphabet)]
    return ciphertext


flag = "NMARK{redacted}"
key = random.randint(1, len(alphabet) - 1)

ciphertext = caesar_cipher(flag, key)

print(ciphertext)
