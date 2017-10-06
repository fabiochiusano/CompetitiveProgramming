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

typedef long long ll;

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
