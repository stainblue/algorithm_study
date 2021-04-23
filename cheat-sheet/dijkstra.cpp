// 음의 가중치를 갖는 그래프는 댜익스트라 사용 불가

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
#include <queue>
using namespace std;

#define MAX_VERTICES 100000

vector<pair<int, int>> adj[MAX_VERTICES + 1];   // 인접행렬. first : vertex index, second : weight(distance)
int nVertices, start;                           // 정점의 개수, 시작 정점 번호
int dist[MAX_VERTICES + 1];	                // 출발점으로부터 i'th 정점까지의 거리
// bool isVisit[MAX_VERTICES + 1];                 // i'th 정점을 Y에 추가했는지 알려줌

// void dijkstra() {
// 	fill_n(dist, MAX_VERTICES + 1, INT_MAX);// dist 배열 INT_MAX값으로 초기화
// 	dist[start] = 0;

// 	int cur = start;
// 	while (!isVisit[cur]) {
// 		isVisit[cur] = true;
		
// 		// dist 배열값 갱신
// 		for (int i = 0; i < adj[cur].size(); i++) {
// 			int next = adj[cur][i].first;
// 			int distance = adj[cur][i].second;

// 			if (dist[next] > dist[cur] + distance) {
// 				dist[next] = dist[cur] + distance;
// 			}
// 		}

//                 // dist[i]가 가장 작은 정점 선택
// 		int minDistance = INT_MAX;
// 		for (int i = 1; i <= nVertices; i++) {
// 			if (isVisit[i]) continue;
// 			if (minDistance > dist[i]) {
// 				minDistance = dist[i];
// 				cur = i;
// 			}
// 		}
// 	}
// }

// priority_queue를 사용하여 시간을 단축시킨 버전
void dijkstra(int start) {
	fill_n(dist, MAX_VERTICES + 1, INT_MAX); // dist 배열 INT_MAX값으로 초기화
	priority_queue<pair<int, int>> pq;
	dist[start] = 0;
	pq.emplace(0, start); // pair에서 정렬은 first 오름차순, 이후 second오름차순이기 때문에 dist, 정점 순서로 넣어줌

	while (!pq.empty()) {
		int cur = pq.top().second;
		int curDistance = pq.top().first;
		pq.pop();

		if (dist[cur] < curDistance) continue;

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].first;
			int distance = adj[cur][i].second;

			if (dist[next] > dist[cur] + distance) {
				dist[next] = dist[cur] + distance;
				pq.emplace(dist[next], next);
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

    int nEdges; // 입력할 간선의 개수
	cin >> nVertices >> nEdges >> start;
	for (int i = 1; i <= nEdges; i++) {
        // 입력 예 : 1 3 4 (1에서 3으로 가는 간선의 가중치 4)
		int from, to, distance;
		cin >> from >> to >> distance;
		adj[from].push_back(make_pair(to, distance));
	}

	dijkstra(start);

    // 시작정점에서부터 i'th 정점까지의 거리 출력
    for (int i = 1; i <= nVertices; i++) {
        cout << dist[i] << " ";
    }
	return 0;
}