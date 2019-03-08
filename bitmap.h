#ifndef BITMAP_H
#define BITMAP_H

#include <stddef.h> /* for size_t declaration */

/**
 * bitmap_t - pointer to a bitmap struct
 *
 * The bitmap struct contains an array of integers used to store bits.
 */
typedef struct bitmap *bitmap_t;

/**
 * bitmap_create - Create a bitmap.
 *
 * This function allocates space for a bitmap that has a specified number of
 * bits.
 *
 * numBits: number of bits within bitmap
 *
 * Returns NULL if memory allocation fails. Constructed bitmap otherwise.
 */
bitmap_t bitmap_create(size_t numBits);

/**
 * bitmap_destroy - Destroy a bitmap.
 *
 * This function frees all memory associated with a bitmap.
 *
 * bm: bitmap to destroy
 *
 * Returns -1 if bm is invalid. 0 otherwise.
 */
int bitmap_destroy(bitmap_t bm);

/**
 * bitmap_set_bit - Set a bit to 1.
 *
 * This function sets the bit stored at an index within a bitmap to be 1.
 *
 * bm: bitmap to modify
 * ind: index of bit in bm to set
 *
 * Returns -1 if bm is invalid, ind is not in bounds. 0 otherwise.
 */
int bitmap_set_bit(bitmap_t bm, size_t ind);

/**
 * bitmap_is_bit_set - Checks if a bit is set to 1.
 *
 * This function checks if the bit stored at an index within a bitmap is 1.
 *
 * bm: bitmap to view
 * ind: index of bit in bm to check
 *
 * Returns -1 if bm is invalid, ind is not in bounds. 0 if bit is not set. 1 if bit
 * is set.
 */
int bitmap_is_bit_set(bitmap_t bm, size_t ind);

#endif /* BITMAP_H */
