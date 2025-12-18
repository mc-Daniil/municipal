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


ct = "NMARK{zhml_rlf_buzhmll_jpwoly_huk_h_jvyylja_mshn_dpao_dvykz_nv_zbiitpa}"

for key in range(1, len(alphabet) - 1):
    plaintext = caesar_cipher(ct, key)
    
    if "correct" in plaintext:
        print(plaintext)
