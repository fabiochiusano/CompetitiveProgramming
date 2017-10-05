#include "union_find.cpp"

/*
* Finds the minimum spanning tree of an UNDIRECTED, WEIGHTED graph using Kruskal's algorithm.
* Uses an edge list.
* Runs in O(E*log(V))
*/

USESTD;

int mst_kruskal(vector<pair<int, PII>>& edgeList, VPII& mst_edges, int V) {
	sort(edgeList.begin(), edgeList.end()); // sort by edge weight O(E log E) // note: pair object has built-in comparison function
	int mst_cost = 0;
	UnionFind UF(V); // all V are disjoint sets initially
	for (int i = 0; i < edgeList.size(); i++) { // for each edge, O(E)
		pair<int, PII> front = edgeList[i];
		if (!UF.isSameSet(front.second.first, front.second.second)) { // check
			mst_cost += front.first; // add the weight of e to MST
			mst_edges.push_back(front.second);
			UF.unionSet(front.second.first, front.second.second); // link them
		}
	} // note: the runtime cost of UFDS is very light // note: the number of disjoint sets must eventually be 1 for a valid MST
	return mst_cost;
}


int main() {
	int V = 8;
	VPII mst_edges;

	vector< pair<int, PII>> edgeList; // (weight, two vertices) of the edge
	edgeList.push_back(make_pair(7, PII(0, 1)));
	edgeList.push_back(make_pair(2, PII(1, 2)));
	edgeList.push_back(make_pair(5, PII(2, 7)));
	edgeList.push_back(make_pair(4, PII(7, 6)));
	edgeList.push_back(make_pair(8, PII(6, 1)));
	edgeList.push_back(make_pair(5, PII(3, 1)));
	edgeList.push_back(make_pair(7, PII(5, 1)));
	edgeList.push_back(make_pair(3, PII(6, 5)));
	edgeList.push_back(make_pair(8, PII(5, 3)));
	edgeList.push_back(make_pair(9, PII(5, 4)));
	edgeList.push_back(make_pair(6, PII(3, 4)));

	printf("MST cost = %d (Kruskal’s)\n", mst_kruskal(edgeList, mst_edges, V));
	cout << "Spanning tree:" << endl;
	LOOP(i,0,mst_edges.size()) cout << "(" << mst_edges[i].first << ", " << mst_edges[i].second << ")" << endl;
}