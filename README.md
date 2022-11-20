# Insane Encrypt
This is a simple encryption algorithm which uses a 256 byte key. This algorithms might not be 100% secure, so don't use this in production.

# How to use it
## Generate a random key
You can generate a random key by using generate_key from Key/Key.h. You need to specify the pseudo random number generator by passing its pointer to generate_key;

## Encrypt / Decrypt
Data can be encrypted/decrypted by using iencrypt/idecrypt from Encrypt.h

## Save the key
The key's important part is key->map (256 bytes). This can be stored in a file or wherever you want.

You can use get_key function to get map allocated on heap (You need to free it!).

## Load key
The load key function takes the map part and loads everything.

## Verify Key
The verify_key function takes the key and checks it's paramters. It returns false if key's variables are invalid.

# How does it work
***Note: everytime a random number is required it uses random() with seed set to the hash value of the key.***

The data is encrypted in several steps:
1. During step 2 several random numbers will be used. All those are allocated on heap. 
2. <details>
    <summary>For encryption: </summary>

    The data is encrypted n times. where n is random number of operations:
    * Generate random numbers by repeatedly calling gen_random_numbers.
    * map each byte using the key->map. Every byte is replaced by key->map[byte].
    * shuffle the data.
    * add_xor is called
    * shuffle the data.
    </details>
<details>
    <summary>For Decryption:</summary>

    Decryption is exact opposite of encryption. All the random numbers used previously are used in reverse order.
</details>

## How does it work (Detailed)
<details>
    <summary>Map</summary>

    Each byte is replaced with the byte which is at that index in key->map[]. 
    eg: if key->map = [30, 138, 47, 123, ...]
    0 is replaced by 30, 1 by 138 and so on.
</details>

<details>
    <summary>Unmap</summary>
    
    Each byte is replaced with the byte which is at that index in key->unmap[].
</details>

<details>
    <summary>Shuffle</summary>

    To shuffle the data, it is divided into segments of random length between key->min_row_size and key->max_row_size (it does not form a square! number of column may be more or less). Each segment is called a row here. The last row might contain less bytes than the other rows if (data_length % row size != 0).

    Shuffle has the following steps:
    1. shuffle rows by calling shuffle_row
    2. swap rows: Swap each row with a random row.
    3. shuffle columns by callong shuffle_clmn
    4. every byte is swapped with a random byte from the data.
</details>


<details>
    <summary>shuffle_row</summary>

    It shifts the data in the row by a random number.
</details>


<details>
    <summary>shuffle_clmn</summary>

    It shifts the data at a specific index from each row.
</details>


<details>
    <summary>add_xor</summary>

    1. A variable s is defined as key->map[random index];
    2. Each (except last) byte (i'th byte; i is index of byte in data array) is XORed to j'th byte of key->map[256]. Where j = (i + s + next byte of data) % 256; 
       Then ((s + i) % 256)'th byte of key->map is added to it.
    3. Last byte is XORed and added using key->map[s] byte.

</details>


<details>
    <summary>sub_xor</summary>

    exact opposite of add_xor.
</details>