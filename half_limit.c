#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "bitmap/bitmap.h"

bitmap_t bm;

/* 1 if num is prime, 0 otherwise. */
#define IS_PRIME(num) (!bitmap_is_bit_set(bm, num))

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
	for (int currNum = prime; currNum < max; currNum += prime) {
		bitmap_set_bit(bm, currNum);
	}
}

/**
 * primes_up_to_half_limit- Compute primes up to a number.
 *
 * This function computes the primes of every integer up to a primeMax.
 *
 * primeMax: limit of numbers to sompute primeness
 *
 * Returns -1 if primesMax is not valid, the number of primes encountered
 * otherwise.
 */
static int primes_up_to_half_limit(int primeMax)
{
	int numPrimes = 0;

	if (primeMax < 2)
		return -1;

	int halfLimit = primeMax / 2;

	/* Iterate through numbers, checking if they are prime. */
	for (int currNum = 2; currNum < primeMax; currNum++) {

		/* Mark all multiples of a prime number, up to half the max. */
		if (IS_PRIME(currNum)) {
			mark_multiples(currNum, halfLimit);
			numPrimes++;
		}
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

	bm = bitmap_create(primeMax);

	clock_t startTime = clock();
	int numPrimes = primes_up_to_half_limit(primeMax);
	clock_t endTime = clock();

	bitmap_destroy(bm);

	double totalTime = endTime - startTime;

	printf("There are %d prime numbers below %d.\n", numPrimes, primeMax);

	printf("This program completed in %lf processor time units.\n", totalTime);

	return 0;
}
