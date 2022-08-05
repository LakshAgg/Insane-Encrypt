# Insane Encrypt
This is a simple encryption algorithm which uses a 256 byte key. This algorithms might not be 100% secure, so don't use this in production.

# How to use it
## Generate a random key
You can generate a random key by using generate_key from Key/Key.h.

## Encrypt / Decrypt
Data can be encrypted/decrypted by using iencrypt/idecrypt from Encrypt.h

# How does it work
## key
The key is 256 byte long. It acts as a look up table, to map every byte of data to some other.

## Shuffle
The data is shuffled several times which completely depends on the key. 

## XOR
Every byte of the data is XORd depending on the original data and the key. 

## Together
All these are executed random number of times depending on the key:

1. The key is hashed to forma single 4 byte number, which is used as a seed for the random generator.
2. At every step of shuffling, n'th byte of key is used. Where n is generated using random().
3. Data is xord