#include "competitive.h"

USESTD;

class UnionFind {
	private:
		VI p, rank, sizes;
		int numSets;
	public:
		UnionFind(int N) {
			rank.assign(N, 0);
			p.assign(N, 0);
			sizes.assign(N,1);
			numSets = N;
			for (int i = 0; i < N; i++) p[i] = i;
		}

		int findSet(int i) {
			return (p[i] == i) ? i : (p[i] = findSet(p[i]));
		}
		bool isSameSet(int i, int j) {
			return findSet(i) == findSet(j);
		}
		void unionSet(int i, int j) {
			if (!isSameSet(i, j)) { // if from different set
				int x = findSet(i), y = findSet(j);
				if (rank[x] > rank[y]) {
					p[y] = x; // rank keeps the tree short
					sizes[x] += sizes[y];
				} else {
					p[x] = y;
					sizes[y] += sizes[x];
					if (rank[x] == rank[y]) rank[y]++;
				}
				numSets--;
			}
		}
		int numDisjointSets() {
			return numSets;
		}
		int sizeOfSet(int i) {
			return sizes[findSet(i)];
		}
};

/*
int main() {
	auto uf = UnionFind(10);

	cout << "ID of 3 is " << uf.findSet(3) << endl;
	cout << "ID of 7 is " << uf.findSet(7) << endl;
	cout << "Are 3 and 7 in the same set: " << uf.isSameSet(3,7) << endl;
	cout << "The set of 3 has size " << uf.sizeOfSet(3) << endl;
	cout << "There are " << uf.numDisjointSets() << " disjoint sets" << endl;

	uf.unionSet(1,3);
	uf.unionSet(7,9);

	cout << "ID of 3 is " << uf.findSet(3) << endl;
	cout << "ID of 7 is " << uf.findSet(7) << endl;
	cout << "Are 3 and 7 in the same set: " << uf.isSameSet(3,7) << endl;
	cout << "The set of 3 has size " << uf.sizeOfSet(3) << endl;
	cout << "There are " << uf.numDisjointSets() << " disjoint sets" << endl;

	uf.unionSet(1,9);

	cout << "ID of 3 is " << uf.findSet(3) << endl;
	cout << "ID of 7 is " << uf.findSet(7) << endl;
	cout << "Are 3 and 7 in the same set: " << uf.isSameSet(3,7) << endl;
	cout << "The set of 3 has size " << uf.sizeOfSet(3) << endl;
	cout << "There are " << uf.numDisjointSets() << " disjoint sets" << endl;

	return 0;
}
*/