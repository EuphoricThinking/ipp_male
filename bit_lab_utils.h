#ifndef BIT_LAB_UTILS_H
#define BIT_LAB_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DIV_64(x) ((x) >> 6)
#define MOD_64(x) ((x) & (((uint64_t)1 << 6) - 1))
#define MOD_2_32(x) ((x) & (((uint64_t)1 << 32) - 1))

/*
 * Provides structs enabling bitwise operations. Data is stored as a sequence
 * of bits packed in types of the constant width - uint64_t
 */

typedef struct Bitmap {
        uint64_t length;
        uint64_t* array;
} Bitmap;

extern Bitmap* convert_r_to_bitmap(char* r, size_t labyrinth_length);

extern Bitmap* convert_hex_to_bitmap(char* hex, size_t hex_length, uint64_t labyrinth_size);

extern void set_bit(Bitmap* bit_array, uint64_t index);

extern Bitmap* create_bitmap(size_t length);

extern bool is_filled_cell(Bitmap* bit_array, uint64_t index);

extern void delete_bitmap(Bitmap* bit_array);
#endif


