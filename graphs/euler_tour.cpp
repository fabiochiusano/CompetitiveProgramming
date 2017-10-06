#include "competitive.h"

/*
* An Euler path is defined as a path in a graph which visits each edge of the graph exactly once.
* Similarly, an Euler tour/cycle is an Euler path which starts and ends on the same vertex.
*/

USESTD;

void eulerTour(map<int,VPII>& adjList, list<int>& cyc, list<int>::iterator i, int u) {
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		PII v = adjList[u][j];
		if (v.second) { // if this edge can still be used/not removed
			adjList[u][j].second = 0; // make the weight of this edge to be 0 (‘removed’)
			for (int k = 0; k < (int)adjList[v.first].size(); k++) { // remove bi-directional edge
				PII uu = adjList[v.first][k];
				if (uu.first == u && uu.second) {
					adjList[v.first][k].second = 0;
					break;
				}
			}
			eulerTour(adjList, cyc, cyc.insert(i, u), v.first);
		}
	}
}

bool hasEulerTour(map<int,VPII>& adjList) {
	LOOP(i,0,adjList.size()) {
		if (adjList[i].size() % 2 != 0) {
			return false;
		}
	}
	return true;
}

bool hasEulerPath(map<int,VPII>& adjList, int& start, int& end) {
	int numOdds = 0;
	bool startAssigned = false, endAssigned = false;;
	LOOP(i,0,adjList.size()) {
		if (adjList[i].size() % 2 != 0) {
			numOdds++;
			if (!startAssigned) {
				startAssigned = true;
				start = i;
			} else if (!endAssigned) {
				endAssigned = true;
				end = i;
			} else {
				return false;
			}
			
		}
	}
	return true;
}

int main() {
	map<int, VPII> adjList;
	list<int> cyc; // we need list for fast insertion in the middle
	int V = 6;

	LOOP(i,0,V) adjList[i] = VPII();
	adjList[0].push_back(PII(1,1));
	adjList[1].push_back(PII(0,1));
	adjList[1].push_back(PII(2,1));
	adjList[2].push_back(PII(1,1));
	adjList[1].push_back(PII(3,1));
	adjList[3].push_back(PII(1,1));
	adjList[1].push_back(PII(5,1));
	adjList[5].push_back(PII(1,1));
	adjList[2].push_back(PII(3,1));
	adjList[3].push_back(PII(2,1));
	adjList[3].push_back(PII(4,1));
	adjList[4].push_back(PII(3,1));
	adjList[4].push_back(PII(5,1));
	adjList[5].push_back(PII(4,1));
	adjList[4].push_back(PII(0,1));
	adjList[0].push_back(PII(4,1));

	cout << "Has Euler tour: " << hasEulerTour(adjList) << endl;
	int s,e;
	bool ep = hasEulerPath(adjList, s, e);
	cout << "Has Euler path: " << ep << endl;
	cout << "  It start at " << s << " and ends at " << e << endl;
	int start = s;
	eulerTour(adjList, cyc, cyc.begin(), start); // cyc contains an Euler tour starting at A
	printf("%d\n", e);
	for (list<int>::iterator it = cyc.begin(); it != cyc.end(); it++)
		printf("%d\n", *it); // the Euler tour

}