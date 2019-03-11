#include <stdio.h>
#include <assert.h>

#include "bitmap.h"

#define NUM_BITS 1000

bitmap_t bm;

static void test_sets_and_checks(void)
{
	/* Check that all bits are accessible and are not set. */
	for (size_t ind = 0; ind < NUM_BITS; ind++) {
		assert(bitmap_is_bit_set(bm, ind) == 0);
	}

	/* Set some bits and check if they were set. */
	assert(bitmap_set_bit(bm, 0) == 0);
	assert(bitmap_is_bit_set(bm, 0) == 1);

	assert(bitmap_set_bit(bm, NUM_BITS - 1) == 0);
	assert(bitmap_is_bit_set(bm, NUM_BITS - 1) == 1);

	size_t midNum = NUM_BITS / 2;

	assert(bitmap_set_bit(bm, midNum) == 0);
	assert(bitmap_is_bit_set(bm, midNum) == 1);
}

int main(int argc, char **argv)
{
	/* Create bitmap. */
	bm = bitmap_create(NUM_BITS);
	assert(bm);

	test_sets_and_checks();

	/* Destroy bitmap. */
	assert(bitmap_destroy(bm) == 0);

	return 0;
}
