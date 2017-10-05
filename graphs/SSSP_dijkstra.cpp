#include "competitive.h"

/*
* SSSP algorithms:
* - unweighted graph -> modified BFS, O(V+E) with adj list
* - weighted graph without negative cycles (may have negative weights) -> Dijkstra, O((E+V)log(V)) with adj list
* - weighted graph with negative cycles -> Bellman Ford, O(V*E) with adj list
*/

void sssp_dijkstra(map<int, VPII>& adjList, VI& dist, VI& pre, int start) {
	dist[start] = 0;
	pre[start] = -1;

	priority_queue< PII, vector<PII>, greater<PII>> pq;
	pq.push(PII(0, start));

	while (!pq.empty()) { // main loop
		PII front = pq.top();
		pq.pop(); // greedy: get shortest unvisited vertex
		int d = front.first, u = front.second;
		if (d > dist[u]) continue; // this is a very important check
		for (int j = 0; j < (int)adjList[u].size(); j++) {
			PII v = adjList[u][j]; // all outgoing edges from u; v.first = node, v.second = weight
			if (dist[u] + v.second < dist[v.first]) {
				dist[v.first] = dist[u] + v.second; // relax operation
				pre[v.first] = u;
				pq.push(PII(dist[v.first], v.first));
			}
		}
	} // this variant can cause duplicate items in the priority queue
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
	
	sssp_dijkstra(adjList, dist, pre, source);

	cout << "Cost: " << dist[dest] << endl;
	cout << "From " << source << " to " << dest << ":" << endl;
	while (pre[dest] != -1) {
		cout << "(" << dest << ", " << pre[dest] << ")" << endl;
		dest = pre[dest];
	}
}