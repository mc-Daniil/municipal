import random
import itertools


def xor_cipher(plaintext, key):
    return bytes(x ^ y for x, y in zip(plaintext, itertools.cycle(key)))


flag = "NMARK{redacted}"
key = random.randbytes(21)

ciphertext = xor_cipher(flag.encode(), key)

print("ciphertext =", ciphertext.hex())
# invert with bytes.fromhex()

hint = xor_cipher("Can you decrypt this?".encode(), key)
print("hint =", hint.hex())
