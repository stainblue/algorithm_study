#include <algorithm>
using namespace std;

#define MAXN 50000

int parent[MAXN], sz[MAXN];

// void init() {
// 	for (int i = 0; i < MAXN; i++) {
// 		parent[i] = i;
// 		sz[i] = 1;
// 	}
// }

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]); // path compression
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	parent[y] = x;
	sz[x] += sz[y];
}