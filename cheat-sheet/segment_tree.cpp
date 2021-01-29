#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SegmentTree {
private:
	long long* tree;
	int nLeaf;

	void setnLeaf(int n) {
		nLeaf = n;
	}

	void buildTree(vector<long long> &input) {
		tree = new long long[nLeaf * 2];

		for (int i = 0; i < input.size(); i++) 
			tree[nLeaf + i] = input[i];

		for (int i = nLeaf - 1; i > 0; i--)
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}

	long long sum(int node, int nleft, int nright, int left, int right) {
		if (nright < left || nleft > right) return 0;
		if (nleft >= left && nright <= right) return tree[node];
		int nmid = (nleft + nright) / 2;
		return sum(node * 2, nleft, nmid, left, right) + sum(node * 2 + 1, nmid + 1, nright, left, right);
	}
public:
	SegmentTree(vector<long long> &arr) {
		int arrSize = arr.size();
		setnLeaf((1 << ((int)ceil(log2(arrSize)) + 1)));
		buildTree(arr);
	}

	void update(int idx, long long value) {
		int i = nLeaf + idx;
		tree[i] = value;

		for (i /= 2; i >= 1; i /= 2) 
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}

	long long sum(int left, int right) {
		return sum(1, 0, nLeaf - 1, left, right);
	}
};