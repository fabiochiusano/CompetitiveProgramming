#include "../competitive.h"

/*
* Segment trees: used to calculate RminQ, RmaxQ, RsumQ and so on...
* They use O(n*log(n)) storage and take O(n*log(n)) time to build. They have height O(log(n)).
* Queries in O(log n + k), k being the number of retrieved intervals or segments.
* They can be dynamically updated in O(log(n)).
*/

USESTD;

const int ST_MOD_MIN = 1;
const int ST_MOD_MAX = 2;
const int ST_MOD_SUM = 3;
class SegmentTree {
	private: VI st, A;
		int n, mod;
		int parent(int p) {
			return p >> 1;
		}
		int left (int p) {
			return p << 1;
		}
		int right(int p) {
			return (p << 1) + 1;
		}
		int fromArrayIndexToTreeIndex(int arrIndex) {
			int treeIndex = 1;
    		int l = 0, r = n-1;
    		while(l != r) {
    			if (arrIndex <= (l+r)/2) {
    				treeIndex = left(treeIndex);
    				r = (l+r)/2;
    			} else {
    				treeIndex = right(treeIndex);
    				l = (l+r)/2 + 1;
    			}
    		}
    		return treeIndex;
		}
		void build(int p, int L, int R) {
			if (L == R){
    			if (mod == ST_MOD_MIN || mod == ST_MOD_MAX) st[p] = L;
				else if (mod == ST_MOD_SUM) st[p] = A[L];
			}
  			else {
        		build(left(p), L, (L + R)/2);
				build(right(p), (L + R) / 2 + 1, R);
				int p1 = st[left(p)], p2 = st[right(p)];
				if (mod == ST_MOD_MIN) st[p] = (A[p1] <= A[p2]) ? p1 : p2;
				else if (mod == ST_MOD_MAX) st[p] = (A[p1] >= A[p2]) ? p1 : p2;
				else if (mod == ST_MOD_SUM) st[p] = p1 + p2;
			}
		}
        int rmq(int p, int L, int R, int i, int j) {
			if (i > R || j < L) return -1; 
			if (L >= i && R <= j) return st[p];

			int p1 = rmq(left(p) , L , (L+R) / 2, i, j);
			int p2 = rmq(right(p), (L+R) / 2 + 1, R, i, j);
        	
        	if (p1 == -1) return p2;
			if (p2 == -1) return p1;

			if (mod == ST_MOD_MIN) return (A[p1] <= A[p2]) ? p1 : p2;
			else if (mod == ST_MOD_MAX) return (A[p1] >= A[p2]) ? p1 : p2;
			else if (mod == ST_MOD_SUM) return p1 + p2;
		}
	public:
		SegmentTree(const VI &_A, int _mod) {
			// For mod, choose one from ST_MOD_MIN, ST_MOD_MAX and ST_MOD_SUM.
			A = _A;
			n = (int)A.size();
			st.assign(4 * n, 0);
			mod = _mod;
			build(1, 0, n - 1);
    	}
    	int query(int i, int j) {
    		return rmq(1, 0, n - 1, i, j);
    	}
    	void update(int index, int value) {
    		A[index] = value;
    		int treeIndex = fromArrayIndexToTreeIndex(index);
    		if (mod == ST_MOD_SUM) st[treeIndex] = value;
    		treeIndex = parent(treeIndex);
    		while(treeIndex > 0) {
    			int p1 = st[left(treeIndex)], p2 = st[right(treeIndex)];
    			if (mod == ST_MOD_MIN) st[treeIndex] = (A[p1] <= A[p2]) ? p1 : p2;
				else if (mod == ST_MOD_MAX) st[treeIndex] = (A[p1] >= A[p2]) ? p1 : p2;
				else if (mod == ST_MOD_SUM) st[treeIndex] = p1 + p2;
    			treeIndex = parent(treeIndex);
    		}
    	}
};


int main() {
	VI A = {3,5,7,9,2,7,1,0,6,4};
	SegmentTree st = SegmentTree(A, ST_MOD_MIN);
	cout << "Min from 2 to 5 is at index " << st.query(2,5) << endl; // 4
	cout << "Min from 6 to 9 is at index " << st.query(6,9) << endl; // 7
	cout << "Min from 0 to 9 is at index " << st.query(0,9) << endl; // 7
	st.update(4,-1);
	cout << "Set A[4] = -1" << endl;
	cout << "Min from 0 to 9 is at index " << st.query(0,9) << endl; // 4
}