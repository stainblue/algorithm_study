# 다익스트라 알고리즘 (Dijkstra's Algorithm)
***가중치가 음이아닌 그래프***의 단일 출발점에서 다른 모든 정점으로 가는 **최단경로**를 찾는 알고리즘이다.   

가중치가 없는 그래프에서의 최단경로는 BFS를 사용하면 된다. 하지만 가중치가 있는 경우에는 간선의 개수가 가장 적다고 최단경로가 되지 않기 때문에, BFS로는 해결할 수 없다.   
다익스트라 알고리즘을 사용하면 시작 정점에서 다른 모든 정점으로 가는 최단경로를 찾을 수 있기 때문에, 결과적으로 어떤 목적지로의 최단경로를 구할 수 있다.

## 알고리즘
출발 정점을 s 라고 할 때, 각 단계에서 s로부터의 최단경로를 알고 있는 정점으로 구성된 트리에 s로부터 가장 가까운 정점을 한 개씩 추가한다.
간단하게 의사코드로 나타내면 다음과 같다.
```
Y = {}; // s로부터의 최단경로를 알고있는 정점들의 집합
dist[]; // s로부터 i'th 정점까지의 최단경로 배열

dist의 모든 값을 INF값으로 초기화한다;
Y에 s 추가;
dist[s] = 0; // s로부터 s까지의 거리는 0

int v; // s로부터 가장 가까운 정점 v 선언
v = s; // 처음상태에서 s에서 가장 가까운 정점은 s

while (모든 정점에 대한 최단경로를 구했음) {
    v에 인접한 정점들의 거리와 dist 배열의 값을 비교하여 더 작은값으로 갱신한다;
    Y만을 거쳐 s로부터 최단거리에 있는 정점 v를 선택한다;
    Y에 s를 넣는다;
}
```

</br>
다음 그림이 다익스트라 알고리즘의 실행절차를 예로 설명한다.   

![ezgif-7-9681e597af97](https://user-images.githubusercontent.com/44018094/104301691-496fd880-550b-11eb-9abb-db70e30a9234.gif)

</br>

## 구현 1

```c++
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
bool isVisit[MAX_VERTICES + 1];                 // i'th 정점을 Y에 추가했는지 알려줌

void dijkstra() {
	fill_n(dist, MAX_VERTICES + 1, INT_MAX);// dist 배열 INT_MAX값으로 초기화
	dist[start] = 0;

	int cur = start;
	while (!isVisit[cur]) {
		isVisit[cur] = true;
		
		// dist 배열값 갱신
		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].first;
			int distance = adj[cur][i].second;

			if (dist[next] > dist[cur] + distance) {
				dist[next] = dist[cur] + distance;
			}
		}

                // dist[i]가 가장 작은 정점 선택
		int minDistance = INT_MAX;
		for (int i = 1; i <= nVertices; i++) {
			if (isVisit[i]) continue;
			if (minDistance > dist[i]) {
				minDistance = dist[i];
				cur = i;
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

	dijkstra();

    // 시작정점에서부터 i'th 정점까지의 거리 출력
    for (int i = 1; i <= nVertices; i++) {
        cout << dist[i] << " ";
    }
	return 0;
}

```

- 시간복잡도 (V : 정점의 개수, E : 간선의 개수)
    + dist배열 값을 갱신하는 과정에서 모든 간선을 검사하므로 O(E).
    + dist[i]가 가장 작은값을 찾으며 모든 정점에 대한 최단거리를 구하기 위해 반복하므로 O(V^2). 

위 두개의 경우를 합하면 총 시간복잡도는 O(E + V^2) 이고,    
우리가 보통 간선이 적은 희소그래프를 다루는 것을 감안하면 E <= V^2 이므로 ***O(V^2)*** 라고 볼 수도 있다.

</br>

## 구현 2 (우선순위 큐 사용)
**구현 1**의 코드에서 dist[i] 가 가장 작은 정점을 구하기 위해 for 반복문을 돌리는 부분을 **우선순위 큐(priority queue)** 를 사용하여 시간을 단축시킬 수 있다.

```c++
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

struct Node {
	int vertex, distance;
};

struct cmp {
	bool operator() (Node a, Node b) {
		// distance 오름차순
		return a.distance > b.distance;
	}
};

void dijkstra() {
	fill_n(dist, MAX_VERTICES + 1, INT_MAX);
	priority_queue<Node, vector<Node>, cmp> pq;
	dist[start] = 0;
	pq.push({ start, 0 });

	while (!pq.empty()) {
		int cur = pq.top().vertex;
		int curDistance = pq.top().distance;
		pq.pop();

		if (dist[cur] < curDistance) continue;

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].first;
			int distance = adj[cur][i].second;

			if (dist[next] > dist[cur] + distance) {
				dist[next] = dist[cur] + distance;
				pq.push({ next, dist[next] });
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

	dijkstra();

	// 시작정점에서부터 i'th 정점까지의 거리 출력
	for (int i = 1; i <= nVertices; i++) {
		cout << dist[i] << " ";
	}
	return 0;
}
```

- 시간복잡도 (V : 정점의 개수, E : 간선의 개수)
    + dist배열 값을 갱신하는 과정에서 모든 간선을 검사하므로 O(E).
    + 모든 간선이 검사될 때 마다 최대 한번 들어갈 수 있기 때문에 우선순위 큐에 들어갈 수 있는 최대 노드의 수는 E개, 추가 혹은 삭제하는 시간 O(log E)이므로 이 둘을 곱하면 O(E log E).

위 두개의 경우를 합하면 총 시간복잡도는 O(E + E log E) = O(E log E)이고,    
우리가 보통 간선이 적은 희소그래프를 다루는 것을 감안하면 E <= V^2 이므로 ***O(E log V)*** 라고 볼 수도 있다.

</br>

## 관련 문제
* [최소비용 구하기 (백준 1916)](https://www.acmicpc.net/problem/1916)
* [최단경로 (백준 1753)](https://www.acmicpc.net/problem/1753)   