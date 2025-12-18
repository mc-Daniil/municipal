import itertools


def xor_cipher(plaintext, key):
    return bytes(x ^ y for x, y in zip(plaintext, itertools.cycle(key)))


ciphertext = bytes.fromhex("6653a882e12bba271dcf307092be3b2aa331e51edb777c8c8fd831a02b1bd13073cbec6514a26aa10f")
hint = bytes.fromhex("6b7f87f0d33fbb6f10d90c6487af2855b436f90180")

key = xor_cipher("Can you decrypt this?".encode(), hint)

plaintext = xor_cipher(ciphertext, key)

print(plaintext.decode())
