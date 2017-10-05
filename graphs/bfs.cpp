#include "competitive.h"

/*
 * BFS runs in O(V+E) with adj list
 */

USESTD;

map<int, VPII> adjList;
int INF = 1000000000;
VI d;

void bfs(map<int, VPII>& adjList, VI& d, int startNode) {
	queue<int> q;
	q.push(startNode);
	while (!q.empty()) {
		int u = q.front(); // queue: layer by layer!
		q.pop();
		cout << "Visited " << u << endl;
		for (int j = 0; j < (int)adjList[u].size(); j++) {
			PII v = adjList[u][j]; // for each neighbor of u
			if (d[v.first] == INF) { // if v.first is unvisited + reachable
				d[v.first] = d[u] + 1; // make d[v.first] != INF to flag it
				q.push(v.first); // enqueue v.first for the next iteration
			}
		}
	}
}

int main() {
	adjList.clear();
	d.clear();
	int V = 6;

	LOOP(i,0,V) {
		adjList[i] = VPII();
	}
	adjList[0].push_back(PII(1,1));
	adjList[0].push_back(PII(4,1));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[3].push_back(PII(5,1));

	LOOP(i,0,V) d.push_back(INF);

	int s = 0; // source is node 0
	d[s] = 0; // distance from source s to s is 0
	
	bfs(adjList, d, s);
}