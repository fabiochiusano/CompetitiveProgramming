#include "competitive.h"

USESTD;

/*
* Used to solve APSP. O(V^3).
* It can also be used for checking transitive closures:
* 	initially, AdjMat[i][j] contains 1 (true) if vertex i is directly connected to vertex j,
* 	0 (false) otherwise. Perform this operation: AdjMat[i][j] |= (AdjMat[i][k] & AdjMat[k][j]).
*	We can check if any two vertices i and j are directly or indirectly connected by checking AdjMat[i][j].
*/

void apsp_warshall(int (&adjMat)[100][100], int (&parent)[100][100], int V) {
	LOOP(i,0,V) LOOP(j,0,V) parent[i][j] = i;
	for (int k = 0; k < V; k++) // remember that loop order is k->i->j
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]) {
					adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
					parent[i][j] = parent[k][j]; // update the parent matrix
				}
}

int main() {
	// precondition: AdjMat[i][j] contains the weight of edge (i, j)
	// or INF (1B) if there is no such edge
	// AdjMat is a 32-bit signed integer array
	int INF = 1000000000;
	int adjMat[100][100];
	int parent[100][100];
	int V = 6;

	LOOP(i,0,100) LOOP(j,0,100) adjMat[i][j] = INF;
	adjMat[0][1] = 3; adjMat[1][0] = 3;
	adjMat[1][2] = 4; adjMat[2][1] = 4;
	adjMat[1][3] = 2; adjMat[3][1] = 2;
	adjMat[1][4] = 1; adjMat[4][1] = 1;
	adjMat[3][4] = 5; adjMat[4][3] = 5;

	apsp_warshall(adjMat, parent, V);

	int source = 3;
	int dest = 0;
	cout << "Cost: " << adjMat[source][dest] << endl;
	cout << "Path: ";
	while (parent[source][dest] != source) {
		cout << dest << " ";
		dest = parent[source][dest];
	}
	cout << dest << " " << source << endl;
}