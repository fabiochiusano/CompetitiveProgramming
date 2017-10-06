#include "../competitive.h"

/*
* Floyd's cycle finding algorithm (aka tortoise & hare algorithm).
*   mu = index of the start of the cycle
*   lambda = length of the cycle
*/

USESTD;

PII floydCycleFinding(map<int,int>& m, int start) { // function int f(int x) is defined earlier
	// 1st part: finding k*mu, hare’s speed is 2x tortoise’s
	int tortoise = m[start], hare = m[m[start]]; // f(x0) is the node next to x0
	while (tortoise != hare) { tortoise = m[tortoise]; hare = m[m[hare]]; }
	// 2nd part: finding mu, hare and tortoise move at the same speed
	int mu = 0; hare = start;
	while (tortoise != hare) { tortoise = m[tortoise]; hare = m[hare]; mu++;}
	// 3rd part: finding lambda, hare moves, tortoise stays
	int lambda = 1; hare = m[tortoise];
	while (tortoise != hare) { hare = m[hare]; lambda++; }
	return PII(mu, lambda);
}

int main() {
	map<int,int> m;
	m[0] = 1;
	m[1] = 2;
	m[2] = 3;
	m[3] = 4;
	m[4] = 5;
	m[5] = 6;
	m[6] = 7;
	m[7] = 3;

	int start = 0;
	PII p = floydCycleFinding(m, start);
	cout << "Mu: " << p.first << ", Lambda: " << p.second << endl;
}