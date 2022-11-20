/**
 * @file Key.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-07-30
 */
#ifndef KEY__HEADER
#define KEY__HEADER
#include <stdbool.h>

/**
 * @brief Just a struct to map one byte to another
 */
struct s_key
{
    unsigned char map[256];
    unsigned char unmap[256];
    unsigned int max_iterations, min_iterations, min_row_size, max_row_size;
    unsigned int seed;
    bool set_seed;
};
typedef struct s_key * key;

/**
 * @brief Generates a random key.
 * @param random_number_gen function which returns a random unsigned char
 * @return key | to be freed by using free() from stdlib.h
 */
key generate_key(unsigned char random_number_gen());

/**
 * @brief Returns the key in form of an array of 256 bytes.
 * @param k 
 * @return void* | to be freed by using free() from stdlib.h
 */
void *get_key(key k);


/**
 * @brief Checks if key is valid.
 * @param k 
 * @return bool 
 */
bool verify_key(key k);

/**
 * @brief Loads the key into the key struct. Warning: load_key does not verify the key.
 * @param k 
 * @return key | to be freed by using free() from stdlib.h
 */
key load_key(void *k);
#endif