#include "competitive.h"

/*
* SSSP algorithms:
* - unweighted graph -> modified BFS, O(V+E) with adj list
* - weighted graph without negative cycles (may have negative weights) -> Dijkstra, O((E+V)log(V)) with adj list 
* - weighted graph with negative cycles -> Bellman Ford, O(V*E) with adj list
*/

void sssp_bf(map<int, VPII>& adjList, VI& dist, VI& pre, int source) {
	dist[source] = 0;
	pre[source] = -1;
	for (int i = 0; i < adjList.size() - 1; i++) // relax all E edges V-1 times
		for (int u = 0; u < adjList.size(); u++) // these two loops = O(E), overall O(VE)
			for (int j = 0; j < (int)adjList[u].size(); j++) {
				PII v = adjList[u][j]; // record SP spanning here if needed
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pre[v.first] = u;
				}
			}
}


int main() {
	int INF = 1000000000;
	int V = 6;
	map<int, VPII> adjList;
	adjList[0].push_back(PII(1,2));
	adjList[0].push_back(PII(3,6));
	adjList[1].push_back(PII(5,7));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(4,4));
	adjList[2].push_back(PII(4,3));
	adjList[2].push_back(PII(3,1));
	adjList[2].push_back(PII(5,3));
	adjList[3].push_back(PII(5,1));
	adjList[4].push_back(PII(3,4));
	VI dist(V, INF);
	VI pre(V, 0);

	int source = 0;
	int dest = 5;
	sssp_bf(adjList, dist, pre, source);

	cout << "Cost: " << dist[dest] << endl;
	cout << "From " << source << " to " << dest << ":" << endl;
	while (pre[dest] != -1) {
		cout << "(" << dest << ", " << pre[dest] << ")" << endl;
		dest = pre[dest];
	}
}