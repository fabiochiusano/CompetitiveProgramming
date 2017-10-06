#include "competitive.h"

/*
* Max network flow with Edmonds-Karp algorithm. O(V*E^2).
* Can also be used to solve Maximum Cardinality Bipartite Matching MCBM.
*/

USESTD;

int INF = 1000000000;

void augment(int (&res)[400][400], VI& p, int s, int v, int minEdge, int& f) { // traverse BFS spanning tree from s->t
	if (v == s) {
		f = minEdge; // record minEdge in a global var f
		return;
	}
	else if (p[v] != -1) {
		augment(res, p, s, p[v], min(minEdge, res[p[v]][v]), f);
		res[p[v]][v] -= f;
		res[v][p[v]] += f;
	}
}

void max_flow_EK(int (&res)[400][400], VI& p, int s, int t, int MAX_V, int& mf) {
	while (1) { // O(VE^2) (actually O(V^3 E) Edmonds Karp’s algorithm
		int f = 0;
		
		VI dist(MAX_V, INF);
		p.assign(MAX_V, -1); // record the BFS spanning tree, from s to t!

		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (u == t) break; // Immediately stop BFS if we already reach sink t
			for (int v = 0; v < MAX_V; v++)
				if (res[u][v] > 0 && dist[v] == INF) {
					dist[v] = dist[u] + 1;
					q.push(v);
					p[v] = u;
				}
		}
		augment(res, p, s, t, INF, f); // find the min edge weight ‘f’ in this path, if any
		if (f == 0) break; // we cannot send any more flow (‘f’ = 0), terminate
		mf += f; // we can still send a flow, increase the max flow!
	}
}

int main() {
	int mf = 0; // mf stands for max_flow
	int MAX_V = 6;

	int res[400][400]; // residual graph
	LOOP(i,0,MAX_V) LOOP(j,0,MAX_V) res[i][j] = 0;
	res[0][1] = 6;
	res[0][2] = 6;
	res[1][3] = 5;
	res[1][4] = 2;
	res[2][3] = 4;
	res[2][4] = 3;
	res[3][5] = 6;
	res[4][5] = 4;

	VI p; // p stores the BFS spanning tree from s
	int s = 0, t = 5;

	max_flow_EK(res, p, s, t, MAX_V, mf);
	
	printf("%d\n", mf); // this is the max flow value
}

