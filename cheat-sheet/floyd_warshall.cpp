// 모든 정점쌍에 대해 최단거리 찾기
// 음수 가중치 사용 가능
// O(N^3)
#include <iostream>
#include <algorithm>
using namespace std; 

int N, M;
const int maxN = 100, INF = 100'000;
int dist[maxN + 1][maxN + 1];

void floyd_warshall() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	// init dist
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}

	for (int i = 0; i < M; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		dist[from][to] = weight;
	}

	floyd_warshall();

	// print
	
	return 0;
}
