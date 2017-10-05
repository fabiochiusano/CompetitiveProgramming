#include "competitive.h"

/*
 * It's just a slightly modified DFS. It runs in O(V+E) with adj list
 */

USESTD;

map<int, VPII> adjList;
VI dfs_num; // global variable, initially all values are set to UNVISITED
VI topo_order;
int UNVISITED = 0, VISITED = 1;

void topological_sort_aux(map<int, VPII>& adjList, VI& dfs_num, int startNode, VI& topo_order) {
	dfs_num[startNode] = VISITED; // important: we mark this vertex as visited
	for (int j = 0; j < (int)adjList[startNode].size(); j++) { // default DS: AdjList
		PII v = adjList[startNode][j]; // v is a (neighbor, weight) pair
		if (dfs_num[v.first] == UNVISITED) // important check to avoid cycle
			topological_sort_aux(adjList, dfs_num, v.first, topo_order); // recursively visits unvisited neighbors of vertex u
	}
	topo_order.push_back(startNode);
}

void topological_sort(map<int, VPII>& adjList, VI& dfs_num, int startNode, VI& topo_order) { // DFS for normal usage: as graph traversal algorithm
	LOOP(i,0,adjList.size()) {
		if (dfs_num[i] == UNVISITED) {
			topological_sort_aux(adjList, dfs_num, i, topo_order);
		}
	}
}

int main() {
	adjList.clear();
	dfs_num.clear();
	topo_order.clear();
	int V = 10;

	LOOP(i,0,V) {
		adjList[i] = VPII();
		dfs_num.push_back(UNVISITED);
	}
	adjList[0].push_back(PII(1,1));
	adjList[0].push_back(PII(4,1));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[3].push_back(PII(5,1));
	adjList[6].push_back(PII(7,1));
	adjList[6].push_back(PII(8,1));

	topological_sort(adjList, dfs_num, 0, topo_order);

	cout << "Order: ";
	for (int i = topo_order.size()-1; i >= 0; i--) {
		cout << topo_order[i] << " ";
	}
	cout << endl;
}