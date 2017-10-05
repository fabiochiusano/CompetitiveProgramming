#include "competitive.h"

/*
* Finds SCC in a directed graph.
* Time complexity of O(V+E), since it uses a modified DFS.
*/

USESTD;

map<int, VPII> adjList;
VI dfs_num, dfs_low, S, visited;
int UNVISITED = 1000000000;


void tarjanSCC(map<int, VPII>& adjList, VI& dfs_num, VI& dfs_low, VI& S, VI& visited, int startNode, int& dfsNumberCounter, int& numSCC) {
	dfs_low[startNode] = dfs_num[startNode] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	S.push_back(startNode); // stores u in a vector based on order of visitation
	visited[startNode] = 1;
	for (int j = 0; j < (int)adjList[startNode].size(); j++) {
		PII v = adjList[startNode][j];
		if (dfs_num[v.first] == UNVISITED)
			tarjanSCC(adjList, dfs_num, dfs_low, S, visited, v.first, dfsNumberCounter, numSCC);
		if (visited[v.first]) // condition for update
			dfs_low[startNode] = min(dfs_low[startNode], dfs_low[v.first]);
	}
	if (dfs_low[startNode] == dfs_num[startNode]) { // if this is a root (start) of an SCC
		printf("SCC %d:", ++numSCC); // this part is done after recursion
		while (1) {
			int v = S.back();
			S.pop_back();
			visited[v] = 0;
			printf(" %d", v);
			if (startNode == v) break;
		}
		printf("\n");
	}
}

int main() {
	int V = 6;

	adjList.clear();
	dfs_num.assign(V, UNVISITED);
	dfs_low.assign(V, 0);
	visited.assign(V, 0);
	S.clear();

	LOOP(i,0,V) adjList[i] = VPII();
	adjList[0].push_back(PII(1,1));
	adjList[0].push_back(PII(4,1));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[3].push_back(PII(5,1));
	adjList[3].push_back(PII(0,1));
	adjList[2].push_back(PII(1,1));

	int dfsNumberCounter = 0;
	int numSCC = 0;
	for (int i = 0; i < V; i++)
		if (dfs_num[i] == UNVISITED)
			tarjanSCC(adjList, dfs_num, dfs_low, S, visited, i, dfsNumberCounter, numSCC);
}