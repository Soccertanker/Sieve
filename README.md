# Sieve of Eratosthenes

This repository explores the speed of some minor improvements that can be made
to the Sieve of Eratosthenes.

## Usage

One must run make and then run an executable with the command line argument
indicating the upper limit for prime numbers.

```bash
make

./<executable> <prime_limit>
```

## Executables

The improvements are cumulative. Every executable implements improvements made
by executables above it.

basic.x implements a basic Sieve.

half\_limit.x marks out multiples of primes only if the prime number is less than
half of \<prime\_limit\>.

square\_start.x starts marking multiples of a prime number at the square of the
prime number.

no\_evens.x does not bother with even numbers.
