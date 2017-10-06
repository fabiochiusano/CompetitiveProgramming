#include "../competitive.h"

/*
* Fenwick trees: used to calculate RsumQ.
* They are a (shorter) alternative to segment trees... similar performance.
* Value updates in practically O(1), so it can be built in O(n).
* Queries done in O(log(n)).
*/

USESTD;

int LSOne(int S) {
	return (S & (-S));
}
class FenwickTree {
	public:
		VI ft;
		FenwickTree(int n) {
			ft.assign(n + 1, 0); // init n + 1 zeroes
		}

		int rsq(int b) { // returns RSQ(1, b)
			int sum = 0;
			for (; b; b -= LSOne(b)) sum += ft[b];
			return sum;
		}
        
        int rsq(int a, int b) { // returns RSQ(a, b)
			return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
		}

    	// adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
    	void adjust(int k, int v) { // note: n = ft.size() - 1
			for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v;
		}

		// update index k with value v
		void update(int k, int v) {
			adjust(k, v - rsq(k,k));
		}
};

int main() {
	FenwickTree ft = FenwickTree(10);
	ft.adjust(1,3);
	ft.adjust(2,5);
	ft.adjust(3,7);
	ft.adjust(4,9);
	ft.adjust(5,2);
	ft.adjust(6,7);
	ft.adjust(7,1);
	ft.adjust(8,0);
	ft.adjust(9,6);
	ft.adjust(10,4);

	cout << "RSQ from 2 to 5 is " << ft.rsq(2,5) << endl; // 23
	cout << "RSQ from 6 to 9 is " << ft.rsq(6,9) << endl; // 14
	cout << "RSQ from 1 to 10 is " << ft.rsq(1,10) << endl; // 44
	ft.update(4, -1);
	cout << "Set A[4] = -1" << endl;
	cout << "RSQ from 1 to 10 is " << ft.rsq(1,10) << endl; // 34
}