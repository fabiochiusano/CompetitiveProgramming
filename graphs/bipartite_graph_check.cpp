#include "competitive.h"

/*
 * Bipartite graph checking is done with a BFS. So, it runs in O(V+E) with adj list
 */

USESTD;

map<int, VPII> adjList;
int NO_COLOR = 0, WHITE = 1, BLACK = 2;
VI colors;

bool bipartite_graph_check(map<int, VPII>& adjList, VI& colors, int startNode) {
	queue<int> q;
	q.push(startNode);
	while (!q.empty()) {
		int u = q.front(); // queue: layer by layer!
		q.pop();
		for (int j = 0; j < (int)adjList[u].size(); j++) {
			PII v = adjList[u][j]; // for each neighbor of u
			if (colors[v.first] == NO_COLOR) { // if v.first is unvisited + reachable
				if (colors[u] == WHITE) colors[v.first] = BLACK;
				else if (colors[u] == BLACK) colors[v.first] = WHITE;
				q.push(v.first); // enqueue v.first for the next iteration
			}
			else if (colors[v.first] == colors[u]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	// Example with bipartite graph
	adjList.clear();
	colors.clear();
	int V = 6;

	LOOP(i,0,V) {
		adjList[i] = VPII();
		colors.push_back(NO_COLOR);
	}
	adjList[0].push_back(PII(1,1));
	adjList[1].push_back(PII(0,1));
	adjList[1].push_back(PII(2,1));
	adjList[2].push_back(PII(1,1));
	adjList[1].push_back(PII(3,1));
	adjList[3].push_back(PII(1,1));
	adjList[3].push_back(PII(4,1));
	adjList[4].push_back(PII(3,1));

	int s = 0; // source is node 0
	colors[s] = WHITE;
	bool is_bip = bipartite_graph_check(adjList, colors, s);
	cout << "Is bipartite graph: " << is_bip << endl;


	// Example with not bipartite graph
	adjList.clear();
	colors.clear();
	V = 6;

	LOOP(i,0,V) {
		adjList[i] = VPII();
		colors.push_back(NO_COLOR);
	}
	adjList[0].push_back(PII(1,1));
	adjList[0].push_back(PII(4,1));
	adjList[1].push_back(PII(2,1));
	adjList[1].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[3].push_back(PII(5,1));

	s = 0; // source is node 0
	colors[s] = WHITE;
	is_bip = bipartite_graph_check(adjList, colors, s);
	cout << "Is bipartite graph: " << is_bip << endl;
}