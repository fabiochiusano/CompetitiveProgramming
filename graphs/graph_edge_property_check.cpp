#include "competitive.h"

/*
 * Finds:
 * - dfs edges
 * - back edges -> if at least one is present, there are cycles
 * - forward/cross edges
 * - two ways edges
 * It uses a DFS, so it takes O(V+E) with adj list
 */

USESTD;

map<int, VPII> adjList;
VI dfs_num, dfs_parent;
int UNVISITED = 0, VISITED = 1, EXPLORED = 2;

void check_edge_property(map<int, VPII>& adjList, VI& dfs_num, int startNode) { // DFS for normal usage: as graph traversal algorithm
	dfs_num[startNode] = EXPLORED; 
	for (int j = 0; j < (int)adjList[startNode].size(); j++) { // default DS: AdjList
		PII v = adjList[startNode][j]; // v is a (neighbor, weight) pair
		if (dfs_num[v.first] == UNVISITED) {
			dfs_parent[v.first] = startNode;
			check_edge_property(adjList, dfs_num, v.first); // recursively visits unvisited neighbors of vertex u
		}
		else if (dfs_num[v.first] == EXPLORED) { // EXPLORED->EXPLORED
			if (v.first == dfs_parent[startNode]) // to differentiate these two cases
				printf(" Two ways (%d, %d)-(%d, %d)\n", startNode, v.first, v.first, startNode);
			else // the most frequent application: check if the graph is cyclic
				printf(" Back Edge (%d, %d) (Cycle)\n", startNode, v.first);
		}
		else if (dfs_num[v.first] == VISITED) // EXPLORED->VISITED
			printf(" Forward/Cross Edge (%d, %d)\n", startNode, v.first);
	}
	dfs_num[startNode] = VISITED;
}

int main() {
	adjList.clear();
	dfs_num.clear();
	dfs_parent.clear();
	int V = 6;

	LOOP(i,0,V) {
		adjList[i] = VPII();
		dfs_num.push_back(UNVISITED);
		dfs_parent.push_back(UNVISITED);
	}
	adjList[0].push_back(PII(1,1));
	adjList[0].push_back(PII(4,1));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[3].push_back(PII(5,1));
	adjList[3].push_back(PII(0,1));
	adjList[2].push_back(PII(1,1));

	int cc_num = 0;
	LOOP(i,0,V) {
		if (dfs_num[i] == UNVISITED) {
			cc_num++;
			cout << "CC " << cc_num << ": " << endl;
			check_edge_property(adjList, dfs_num, i);
		}
	}
}