#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"

#if 0
#define BM_IS_VALID(bm) (!bm || !(bm->ar) ? -1 : 0)
#else
#define BM_IS_VALID(bm) 1
#endif

/* number of bits in each integer of the bitmap array */
#define BM_BITS_PER_INT 8

#define BM_BITS_PER_BYTE 8 /* trivial */

/* ceiling division of a/b */
#define CEIL_DIV(a, b) (a / b + (a % b != 0))

/**
 * struct bitmap - Stores bits that are 0 or 1.
 *
 * numBits: number of bits within the bitmap
 * @ar: array of bytes where bits are stored, each element is BM_BITS_PER_INT
 * bits in length
 */
struct __attribute__ ((packed)) bitmap {
	size_t numBits;
	uint8_t *ar;
};

bitmap_t bitmap_create(size_t numBits)
{
	bitmap_t bm = (bitmap_t)malloc(sizeof(struct bitmap));
	if (!bm)
		return NULL;

	size_t numBytes = CEIL_DIV(numBits, BM_BITS_PER_INT);
	bm->ar = (uint8_t *)malloc(numBytes);
	if (!(bm->ar)) {
		free(bm);
		return NULL;
	}

	bm->numBits = numBits;

	return bm;
}

int bitmap_destroy(bitmap_t bm)
{
	if (!BM_IS_VALID(bm))
		return -1;

	free(bm);

	return 0;
}

/* Converts from bit index to array index in bitmap. */
#define BM_AR_IND(ind) (ind / BM_BITS_PER_INT)

/* Converts from bit index to bit index within integer. */
#define BM_INT_IND(ind) (ind % BM_BITS_PER_INT)

/* Make a mask for a bit of an integer. */
#define BM_MASK(ind) (BM_INT_IND(ind) << ind)

/* Set a bit by or'ing the bitmap with a mask that contains a single 1. */
#define BM_SET_BIT(bm, ind) (bm->ar[BM_AR_IND(ind)] |= BM_MASK(ind))

int bitmap_set_bit(bitmap_t bm, size_t ind)
{
	/* TODO */
	if (!BM_IS_VALID(bm))
		return -1;

	BM_SET_BIT(bm, ind);

	return 0;
}

/* Get a bit by and'ing the bitmap with a mask that contains a single 1. */
#define BM_GET_BIT(bm, ind) (bm->ar[BM_AR_IND(ind)] & BM_MASK(ind))

/* Check if a bit is set by seeing if the bit is not zero. */
#define BM_IS_BIT_SET(bm, ind) (BM_GET_BIT(bm, ind) != 0)

int bitmap_is_bit_set(bitmap_t bm, size_t ind)
{
	/* TODO */
	if (!BM_IS_VALID(bm))
		return -1;

	if (BM_IS_BIT_SET(bm, ind))
		return 1;

	return 0;
}
