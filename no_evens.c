#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "bitmap/bitmap.h"

bitmap_t bm;

/* 1 if num is prime, 0 otherwise. */
#define IS_PRIME(num) (!bitmap_is_bit_set(bm, NUM_TO_IND(num)))

#define NUM_TO_IND(num) ((num / 2) - 1)

/**
 * mark_multiples - Mark all multiples of a prime number.
 *
 * This function goes through the bitmap, marking every multiple of a prime
 * number as composite.
 *
 * prime: number to mark multiples of
 * max: only mark multiples that are smaller than max
 */
static void mark_multiples(int prime, int max)
{
	long long int primeLong = (long long int)prime;
	long long int start = primeLong * primeLong;
	if (start > max)
		return;

	for (int currNum = start; currNum < max; currNum += (prime * 2)) {
		bitmap_set_bit(bm, NUM_TO_IND(currNum));
	}
}

/**
 * primes_up_to_no_evens - Compute primes up to a number.
 *
 * This function computes the primes of every integer up to a primeMax.
 *
 * primeMax: limit of numbers to sompute primeness
 *
 * Returns -1 if primesMax is not valid, the number of primes encountered
 * otherwise.
 */
static int primes_up_to_no_evens(int primeMax)
{
	/* We do not store evens, so we begin with one prime number, p=2. */
	int numPrimes = 1;

	if (primeMax < 2)
		return -1;

	int halfLimit = primeMax / 2;

	/* Begin searching for prime numbers at p=3. */
	int currNum = 3;

	/* Iterate through odd numbers, checking if they are prime. */
	for (; currNum < halfLimit; currNum += 2) {

		/* Mark all multiples of a prime number. */
		if (IS_PRIME(currNum)) {
			mark_multiples(currNum, primeMax);
			numPrimes++;
		}
	}

	/* Search for any remaining primes between halfLimit and primeMax. */
	for (; currNum < primeMax; currNum += 2) {
		if (IS_PRIME(currNum))
			numPrimes++;
	}

	return numPrimes;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: ./<exec> prime_max\n");
		return 1;
	}

	int primeMax = atoi(argv[1]);

	/* Bitmap only stores odd numbers now. */
	bm = bitmap_create(primeMax / 2);

	clock_t startTime = clock();
	int numPrimes = primes_up_to_no_evens(primeMax);
	clock_t endTime = clock();

	bitmap_destroy(bm);

	double totalTime = endTime - startTime;

	printf("There are %d prime numbers below %d.\n", numPrimes, primeMax);

	printf("This program completed in %lf processor time units.\n", totalTime);

	return 0;
}
