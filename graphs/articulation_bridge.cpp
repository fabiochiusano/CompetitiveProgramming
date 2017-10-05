#include "competitive.h"

/*
* Articulation points and bridges in an UNDIRECTED graph.
* Time complexity of O(V+E), since it uses a modified DFS.
*/

USESTD;

map<int, VPII> adjList;
VI dfs_num, dfs_low, dfs_parent, articulation_vertex;
int UNVISITED = 1000000000;


void articulationPointAndBridge(map<int, VPII>& adjList, VI& dfs_num, VI& dfs_low, VI& dfs_parent, VI& articulation_vertex, int startNode, int& dfsRoot, int& rootChildren, int& dfsNumberCounter) {
	dfs_low[startNode] = dfs_num[startNode] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	for (int j = 0; j < (int)adjList[startNode].size(); j++) {
		PII v = adjList[startNode][j];
		if (dfs_num[v.first] == UNVISITED) {
			dfs_parent[v.first] = startNode;
			if (startNode == dfsRoot) rootChildren++;
			articulationPointAndBridge(adjList, dfs_num, dfs_low, dfs_parent, articulation_vertex, v.first, dfsRoot, rootChildren, dfsNumberCounter);
			if (dfs_low[v.first] >= dfs_num[startNode])
				articulation_vertex[startNode] = true;
            if (dfs_low[v.first] > dfs_num[startNode])
				printf(" Edge (%d, %d) is a bridge\n", startNode, v.first);
    		dfs_low[startNode] = min(dfs_low[startNode], dfs_low[v.first]); // update dfs_low[u]
    	}
		else if (v.first != dfs_parent[startNode]) // a back edge and not direct cycle
			dfs_low[startNode] = min(dfs_low[startNode], dfs_num[v.first]); // update dfs_low[u]
	}
}

int main() {
	dfs_num.clear();
	dfs_low.clear();
	dfs_parent.clear();
	articulation_vertex.clear();

	int V = 6;

	LOOP(i,0,V) {
		adjList[i] = VPII();
		dfs_num.push_back(UNVISITED);
		dfs_low.push_back(0);
		dfs_parent.push_back(0);
		articulation_vertex.push_back(0);
	}
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

	printf("Bridges:\n");
	int dfsNumberCounter = 0;
	int dfsRoot = 0;
	int rootChildren = 0;
	for (int i = 0; i < V; i++)
		if (dfs_num[i] == UNVISITED) {
			dfsRoot = i;
			rootChildren = 0;
			articulationPointAndBridge(adjList, dfs_num, dfs_low, dfs_parent, articulation_vertex, i, dfsRoot, rootChildren, dfsNumberCounter);
			articulation_vertex[dfsRoot] = (rootChildren > 1);
		}

	printf("Articulation Points:\n");
	for (int i = 0; i < V; i++)
		if (articulation_vertex[i])
			printf(" Vertex %d\n", i);
}