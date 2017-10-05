#include "competitive.h"

/*
* Finds the minimum spanning tree of an UNDIRECTED, WEIGHTED graph using Prim's algorithm.
* Uses a adj list.
* Runs in O(E*log(V))
*/

USESTD;

map<int, VPII> adjList;
VI taken; // global boolean flag to avoid cycle
priority_queue<PII> pq; // priority queue to help choose shorter edges
// note: default setting for C++ STL priority_queue is a max heap

// assume the graph is stored in AdjList, pq is empty
int process(map<int, VPII>& adjList, VI& taken, priority_queue<PII>& pq, int start) { // so, we use - sign to reverse the sort order
	taken[start] = 1;
	for (int j = 0; j < (int)adjList[start].size(); j++) {
		PII v = adjList[start][j];
		if (!taken[v.first])
			pq.push(PII(-v.second, -v.first));
	}
} // sort by (inc) weight then by (inc) id

int mst_prim(map<int, VPII>& adjList, VI& taken, priority_queue<PII>& pq) {
	process(adjList, taken, pq, 0); // take vertex 0 and process all edges incident to vertex 0
	int mst_cost = 0;
	while (!pq.empty()) { // repeat until V vertices (E=V-1 edges) are taken
		PII front = pq.top();
		pq.pop();
		int u = -front.second, w = -front.first; // negate the id and weight again
		if (!taken[u]) { // we have not connected this vertex yet
			mst_cost += w;
			process(adjList, taken, pq, u); // take u, process all edges incident to u
		}
	} // each edge is in pq only once!
	return mst_cost;
}

int main() {
	int V = 6;

	taken.assign(V, 0); // no vertex is taken at the beginning
	LOOP(i,0,V) adjList[i] = VPII();
	adjList[0].push_back(PII(1,1));
	adjList[1].push_back(PII(0,1));
	adjList[1].push_back(PII(2,1));
	adjList[2].push_back(PII(1,1));
	adjList[1].push_back(PII(3,1));
	adjList[3].push_back(PII(1,1));
	adjList[1].push_back(PII(4,1));
	adjList[4].push_back(PII(1,1));
	adjList[1].push_back(PII(5,1));
	adjList[5].push_back(PII(1,1));
	adjList[5].push_back(PII(4,1));
	adjList[4].push_back(PII(5,1));

	
	printf("MST cost = %d (Prim’s)\n", mst_prim(adjList, taken, pq));
}