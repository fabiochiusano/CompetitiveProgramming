#include "../competitive.h"

/*
* Sieve of Eratosthenes: checks if a number N < 10^14 is prime or not.
*   - sieve
*   - isPrime
* 
* Find the prime factors of a number with Optimized Trial Divisions.
*   - sieve
*   - primeFactors
*
* Euler Phi: count the number of positive integers < N that are relatively prime to N.
*   - eulerPhi
*/
 

void sieve(ll upperbound, bitset<10000010>& bs, VI& primes) { // create list of primes in [0..upperbound]
	bs.set();  // set all bits to 1
	bs[0] = bs[1] = 0;  // except index 0 and 1
	for (ll i = 2; i <= upperbound; i++) if (bs[i]) {
		for (ll j = i * i; j <= upperbound; j += i) bs[j] = 0; // cross out multiples of i starting from i * i!
		primes.push_back((int)i); // add this prime to the list of primes
	}
}

bool isPrime(ll N, ll _sieve_size, bitset<10000010>& bs, VI& primes) { // a good enough deterministic prime tester
	if (N <= _sieve_size) return bs[N]; // O(1) for small primes
	for (int i = 0; i < (int)primes.size(); i++)
		if (N % primes[i] == 0) return false;
	return true; // it takes longer time if N is a large prime!
} // note: only work for N <= (last prime in vi "primes")^2

VI primeFactors(ll N, VI& primes) { // remember: vi is vector<int>, ll is long long
	VI factors;
	ll PF_idx = 0, PF = primes[PF_idx]; // primes has been populated by sieve
	while (PF * PF <= N) { // stop at sqrt(N); N can get smaller
		while (N % PF == 0) {
			N /= PF;
			factors.push_back(PF);
		} // remove PF
		PF = primes[++PF_idx]; // only consider primes!
	}
	if (N != 1) factors.push_back(N); // special case if N is a prime
	return factors; // if N does not fit in 32-bit integer and is a prime
} // then ‘factors’ will have to be changed to vector<ll>

ll eulerPhi(ll N, VI& primes) {
	ll PF_idx = 0, PF = primes[PF_idx], ans = N; // start from ans = N 
	while (PF * PF <= N) {
		if (N % PF == 0) ans -= ans / PF; // only count unique factor
		while (N % PF == 0) N /= PF;
		PF = primes[++PF_idx];
	}
	if (N != 1) ans -= ans / N; return ans; // last factor
}

int main() {
	ll _sieve_size = 10000000+1; // add 1 to include upperbound
	bitset<10000010> bs; // 10^7 should be enough for most cases
	VI primes; // compact list of primes in form of vector<int>

	sieve(_sieve_size, bs, primes); // can go up to 10^7 (need few seconds)

	printf("%d\n", isPrime(2147483647, _sieve_size, bs, primes)); // 10-digits prime
	printf("%d\n", isPrime(136117223861LL, _sieve_size, bs, primes)); // not a prime, 104729*1299709

	VI r = primeFactors(2147483647, primes); // slowest, 2147483647 is a prime
	for (VI::iterator i = r.begin(); i != r.end(); i++) printf("> %d\n", *i);

	r = primeFactors(136117223861LL, primes); // slow, 104729*1299709
	for (VI::iterator i = r.begin(); i != r.end(); i++) printf("# %d\n", *i);

	r = primeFactors(142391208960LL, primes); // faster, 2^10*3^4*5*7^4*11*13
	for (VI::iterator i = r.begin(); i != r.end(); i++) printf("! %d\n", *i);
}