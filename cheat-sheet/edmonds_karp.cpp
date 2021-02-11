#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std; 

const int MAXV = 1000;

class maximumFlow {
private:
	struct edge {
		int from, to, capacity, flow;
		edge* reverse;

		edge(int f, int t, int c) : from(f), to(t), capacity(c), flow(0) {}

		int residual() { return capacity - flow; }
		void addFlow(int newFlow) {
			flow += newFlow;
			reverse->flow -= newFlow;
		}
	};

	vector<edge*> adj[MAXV + 1];
	int prev[MAXV + 1];
	edge* backEdge[MAXV + 1];

	// bfs
	bool isAugmentingPathExist() {
		return isAugmentingPathExist(source, sink);
	}

	bool isAugmentingPathExist(int from, int to) {
		for (int i = 0; i < MAXV + 1; i++) {
			prev[i] = -1;
			backEdge[i] = NULL;
		}
		queue<int> q;
		q.push(from);
		while (!q.empty() && prev[to] == -1) {
			int cur = q.front(); q.pop();
			for (auto e : adj[cur]) {
				int next = e->to;
				if (prev[next] == -1 && e->residual() > 0) {
					prev[next] = cur;
					backEdge[next] = e;
					q.push(next);
				}
			}
		}
		if (prev[to] == -1) return false;
		return true;
	}

	int maxFlow = 0;
public:
	int source, sink;

	void addEdge(int from, int to, int capacity, bool directed = true) {
		edge* e = new edge(from, to, capacity);
		edge* er = new edge(to, from, directed ? 0 : capacity);
		e->reverse = er;
		er->reverse = e;
		adj[from].push_back(e);
		adj[to].push_back(er);
	}

	// Edmonds-Karp Algorithm
	int findMaxFlow() {
		while (isAugmentingPathExist()) {
			int newFlow = 1000;

			for (int i = sink; i != source; i = prev[i]) {
				newFlow = min(newFlow, backEdge[i]->residual());
			}

			for (int i = sink; i != source; i = prev[i]) {
				backEdge[i]->addFlow(newFlow);
			}

			maxFlow += newFlow;
		}
		return maxFlow;
	}
};
