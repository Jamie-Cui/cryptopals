# Cryptopals Challenge Set 2

## Implement PKCS#7 padding

Complie from source: `gcc pkcs7.c -o pkcs7`
```
/*
	This function takes 2 parameters:
	1. Blocksize in bytes
	2. Message string
*/
./pkcs7 20 "YELLOW SUBMARIENE"
```

## Implement AES CBC Mode

This implementation uses **openssl library**, and buiding aes\_cbc mode based on aes\_ecb mode. (AEC\_ECB mode simply encrypt each block and concatenate ciphertexts)

Compile from source: `gcc aes_ecb.c -o aes_ecb -lcrypto`
