#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <set>
#include <bitset>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

#define LOOP(i,start,end) for(int i = start; i < end; ++i)
#define USESTD using namespace std
#define FOREACH(el,arr) for(auto& el : arr)

USESTD;

typedef pair<int, int> PII;
typedef pair<int, float> PIF;
typedef pair<int, char> PIC;
typedef pair<int, string> PIS;
typedef pair<string, string> PSS;
typedef pair<char, char> PCC;

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VPII;
typedef vector<PIF> VPIF;
typedef vector<PIC> VPIC;
typedef vector<PIS> VPIS;
typedef vector<PSS> VPSS;
typedef vector<PCC> VPCC;

auto CMP_MAX = [](int a, int b) { return a < b; };
typedef priority_queue<int, vector<int>, decltype(CMP_MAX)> PQ_MAX;
auto CMP_MIN = [](int a, int b) { return a > b; };
typedef priority_queue<int, vector<int>, decltype(CMP_MIN)> PQ_MIN;





VS SPLITSTRING(string& s, string delim) {
	auto start = 0U;
    auto end = s.find(delim);
    VS result;
    while (end != string::npos)
    {
    	string st = s.substr(start, end - start);
    	if (st.size() > 0) result.push_back(st);
        start = end + delim.length();
        end = s.find(delim, start);
    }

    result.push_back(s.substr(start, end));
    return result;
}

int GCD(int u, int v) {
    while (v != 0) {
        int r = u % v;
        u = v;
        v = r;
    }
    return u;
}






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
    	int rmq(int i, int j) {
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
};


// Permutations
/*
* int i, n = 8, p[8] = {0, 1, 2, 3, 4, 5, 6, 7}; // the first permutation
* do {
* 	...
* } while(next_permutation(p, p + n));
*/

// Subsets
/*
* int n = set.size();
* int i; // the bitmask
* for (i = 0; i < (1 << n); i++) { // for each subset, O(2^n)
* 	sum = 0;
*	for (int j = 0; j < n; j++) // check membership, O(n)
*		if (i & (1 << j)) // test if bit ‘j’ is turned on in subset ‘i’
*			sum += l[j]; // if yes, process ‘j’
*	if (sum == X) break; // the answer is found: bitmask ‘i’
* }
*/
