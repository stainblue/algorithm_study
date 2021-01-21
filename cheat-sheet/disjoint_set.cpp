#include <iostream>
using namespace std;

#define DEFAULT_N 500000

class DisjointSet {
private:
	int *parent;
	int *rank;
public:
	DisjointSet() {
		DisjointSet(DEFAULT_N);
	}

	DisjointSet(int N) {
		parent = new int[N];
		rank = new int[N];

		for (int i = 0; i < N; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int i) {
		if (parent[i] == i) return i;
		parent[i] = find(parent[i]); // path compression
		return parent[i];
	}

	void merge(int i, int j) {
		int pi = find(i);
		int pj = find(j);
		if (pi == pj) return;

		// union by rank
		if (rank[pi] > rank[pj]) swap(pi, pj);
		parent[pi] = pj;
		if (rank[pi] == rank[pj]) rank[pj]++;
	}
};
