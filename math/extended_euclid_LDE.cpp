#include "../competitive.h"

/*
* Extended Euclid: Solving Linear Diophantine Equation "ax + by = d".
*/

USESTD;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

// store x, y, and d as global variables
void extendedEuclid(int a, int& x, int b, int& y, int d) {
	if (b == 0) { x = 1; y = 0; d = a; return; } // base case
	extendedEuclid(b, x, a % b, y, d);
	int x1 = y;
	int y1 = x - (a / b) * y;
	x = x1;
	y = y1;
}

void extendedEuclidNatural(int a, int& x, int b, int& y, int d) { // watchout for overflow!
	extendedEuclid(a,x,b,y,d);
	int k = d/gcd(a,b);
	x *= k; y *= k; d *= k;
	bool xPos = x >= 0, yPos = y >= 0;
	int n = 0;
	if (!xPos && yPos) {
		while(!(x + b*n >= 0 && y - a*n >= 0)) n++;
		x += b*n; y -= a*n;
	} else if (xPos && !yPos) {
		while(!(x - b*n >= 0 && y + a*n >= 0)) n++;
		x -= b*n; y += a*n;
	} else if (!xPos && !yPos) {
		while(!(x + b*n >= 0 && y + a*n >= 0)) n++;
		x += b*n; y += a*n;
	}
}

int main() {
	int a = 25, b = 18, d = 839;
	int x, y;
	extendedEuclidNatural(a,x,b,y,d);
	cout << a << "*" << x << " + " << b << "*" << y << " = " << d << endl;
}