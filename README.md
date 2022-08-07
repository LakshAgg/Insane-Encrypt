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

### Initialize
1. The seed of pseudo-random generator is set to the hash value of the key.
2. The data is divided into random number of rows and columns.
3. Data is encrypted random number of times (between max and min iterations).

### Encrypt
1. Every byte of data is mapped to another using the 256 byte key.
2. The data is shuffled.
3. XOR is applied on every byte with the nth element of the key. And the nth element of the key is added to the result. where n is a random number.
4. Data is shuffled again.

### Shuffle
1. Each row is shifted by n. where n is key[random % 256] element.
2. Complete rows are switched by n'th row. where n is key[random % 256] element.
3. Columns are shifted by n. where n is key[random % 256] element..
4. Each byte is swapped with some random index.