#include "competitive.h"

/*
 * DFS runs in O(V+E) with adj list
 */

USESTD;

map<int, VPII> adjList;
VI dfs_num; // global variable, initially all values are set to UNVISITED
int UNVISITED = 0, VISITED = 1;

void dfs(map<int, VPII>& adjList, VI& dfs_num, int startNode) { // DFS for normal usage: as graph traversal algorithm
	dfs_num[startNode] = VISITED; // important: we mark this vertex as visited
	cout << "Visited " << startNode << endl;
	for (int j = 0; j < (int)adjList[startNode].size(); j++) { // default DS: AdjList
		PII v = adjList[startNode][j]; // v is a (neighbor, weight) pair
		if (dfs_num[v.first] == UNVISITED) // important check to avoid cycle
			dfs(adjList, dfs_num, v.first); // recursively visits unvisited neighbors of vertex u
	}
}

int main() {
	adjList.clear();
	dfs_num.clear();
	int V = 6;

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

	int UNVISITED = 0, VISITED = 1;

	int startNode = 0;
	dfs(adjList, dfs_num, startNode);
}