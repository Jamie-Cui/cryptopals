# Cryptopal challenge set 1

This is the qualifying set. We picked the exercises in it to ramp developers up gradually into coding cryptography, but also to verify that we were working with people who were ready to write code.

This set is relatively easy. With one exception, most of these exercises should take only a couple minutes. But don't beat yourself up if it takes longer than that. It took Alex two weeks to get through the set!

If you've written any crypto code in the past, you're going to feel like skipping a lot of this. Don't skip them. At least two of them (we won't say which) are important stepping stones to later attacks. 

## Convert hex to base64

Cryptopal's Rule: Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing. This mission requires to convert one hex string to base64 string, exmaple is shown below: 

- hex: `49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d`
- base64: `SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t`

The answer file includes `hex2base64.c`, to compile from source and test exmaple:
```
gcc hex2base64.c -o hex2base64
./hex2base64 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
```

## Fixed XOR

Write a function that takes two equal-length buffers and produces their XOR combination. 

- m1: `1c0111001f010100061a024b53535009181c`
- m2: `686974207468652062756c6c277320657965`
- m1 xor m2: `746865206b696420646f6e277420706c6179`

To compile from source and test:
```
gcc xor_cipher_fixed.c -o xor_cipher_fixed
./xor_cipher_fixed 1c0111001f010100061a024b53535009181c 686974207468652062756c6c277320657965
```
## Single-byte XOR cipher

 The hex encoded string:

- `1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736`

... has been XOR'd against a single character. Find the key, decrypt the message.

You can do this by hand. But don't: write code to do it for you.

How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric. Evaluate each output and choose the one with the best score. 
