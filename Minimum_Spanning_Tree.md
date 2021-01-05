# 최소비용 신장트리 (Minimum Spanning Tree)
몇개의 점이 주어졌을 때 최소한의 비용으로 그 점들을 연결하는 문제는 모두 최소비용 신장트리로 풀 수 있다.

## 최소비용 신장트리란?
* 트리(Tree) : 사이클(cycle)이 없고 연결되어(connected)있는 비방향(undirected)그래프
* 신장트리(Spanning Tree) : 그래프의 정점(vertex)를 모두 포함하는 트리(Tree)
* 최소비용 신장트리(MST) : 사용된 가중치의 합이 최소인 신장트리

예를들어 왼쪽그림은 최소비용 신장트리이지만 오른쪽그림은 최소비용 신장트리가 아니다.

<img src="https://user-images.githubusercontent.com/44018094/103638223-f5f00e80-4f8f-11eb-886d-c1f892d4b111.png" width="300px" height="300px"></img><img src="https://user-images.githubusercontent.com/44018094/103638263-07391b00-4f90-11eb-9753-1ba65a5bcc77.png" width="300px" height="300px"></img>

최소비용 신장트리를 계산할 때는 주로 **프림 알고리즘 (Prim's Algorithm)** 이나 **크루스칼 알고리즘(Kruskal's Algorithm)** 을 사용한다.   
</br>

### 약간의 응용
* 최대비용 신장트리
    - 최대의 비용으로 점들을 연결하고 싶을 경우
    - 모든 가중치의 부호가 양수일 경우 **모든 가중치의 부호를 음수로 반전**시킨 뒤 프림 / 크루스칼 알고리즘을 적용한다. 이후 결과로 나온 가장 작은값의 가중치를 갖는 트리가 부호를 원래대로 되돌리면 최대비용 신장트리가 된다.
    - 대부분의 그래프 알고리즘은 음수 가중치에 대해서 제대로 작동하지 않으므로 주의가 필요하다.
        + 최단경로 알고리즘은 이 방법을 사용해서 최장경로를 구할 수 없다.
* 최소곱 신장트리
    - 모든 가중치가 양수일때 가중치의 곱이 최소가 되게할 경우
    - **log(ab) = log(a) + log(b)** 를 활용하여 가중치의 로그값으로 알고리즘을 돌린다.
* 최소병목 신장트리
    - 가장 큰 가중치의 개수가 최소가 되는 신장트리를 찾아야 하는 경우
    - 최소비용 신장트리가 이 성질을 만족한다.

### 관련 문제
* [최소 스패닝 트리 (백준 1197)](https://www.acmicpc.net/problem/1197)
* [네트워크 연결 (백준 1922)](https://www.acmicpc.net/problem/1922)   
</br>

***
## 프림 알고리즘 (Prim's Algorithm)
어떤 정점(vertex)에서 시작해서 단계별로 정점들을 선택하여 최소비용 신장트리를 만드는 방법.   
매 선택마다 가장 좋아보이는 것을 선택하기 때문에 탐욕 알고리즘(Greedy Algorithm) 이다.
### 그래프 G=(V, E)의 최소비용 신장트리 T=(Y, F)를 만드는 과정
1. 임의의 정점 하나를 포함하는 Y와 공집합인 F에서 시작한다.
2. Y에서 가장 가까운 정점(vertex)을 Y에 추가하고, 그 간선(edge)은 F에 추가한다. 같은 가중치가 한개 이상 있으면, 임의로 선택한다.
3. **2번** 과정을 Y = V 가 될 때까지 반복한다.

이 절차를 의사코드로 나타내면 다음과 같다.
```
Y = {V1};
F = {};

while (!(Y == V)) {
    Y 에서 가장 가까운 V - Y 에 속한 정점(vertex) 선택;
    그 정점을 Y에 추가;
    그 간선을 F에 추가;
}
```

다음 그림으로 프림 알고리즘이 어떻게 실행되는지 알 수 있다.   
![ANY_0105204704](https://user-images.githubusercontent.com/44018094/103642976-46b73580-4f97-11eb-9d36-0b66b42be23e.gif)

### [코드 예](https://github.com/stainblue/algorithm_study/blob/master/cheat-sheet/prim.cpp)
``` C++
#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
using namespace std;

#define MAX_VERTICES 1000

int adj[MAX_VERTICES + 1][MAX_VERTICES + 1];	// 인접행렬
int isVisit[MAX_VERTICES + 1];			// 이 vertex가  MST = (Y, F)의 Y(vertices 집합)에 포함됐는지 여부
int dist[MAX_VERTICES + 1];			// 이 vertex와 Y와의 최소거리. (이미 포함된 경우 0)
int nVerteices;					// vertex 개수

void prim() {
	dist[1] = 0;						// V1부터 시작
	isVisit[1] = true;					// V1이 Y에 포함됨
	for (int i = 2; i <= nVerteices; i++) {
		if (dist[i] > adj[1][i]) dist[i] = adj[1][i];	// V1과 인접해있는 vertex들의 distance를 adj[1][vertexIndex]로 갱신
	}

	for (int i = 0; i < nVerteices - 1; i++) {		// V1은 이미 Y에 포함됐으므로 N - 1번 반복
		// G = (V, E)의 V - Y 중에서 Y와 가장 가까운 vertex 찾기
		int minDist = INT_MAX;				// 가장 가까운 vertex와의 거리
		int vnear;					// 가장 가까운 vertex의 index
		for (int j = 1; j <= nVerteices; j++) {
			if (!isVisit[j] && dist[j] < minDist) {
				minDist = dist[j];
				vnear = j;
			}
		}

		// index가 vnear인 vertex를 Y에 넣음
		isVisit[vnear] = true;
		// do something
		dist[vnear] = 0;

		// index가 vnear인 vertex가 Y에 추가됐으므로 해당 vertex와 인접한 vertex들의 최소거리만 갱신해주면 됨
		for (int j = 1; j <= nVerteices; j++) {
			if (!isVisit[j] && adj[vnear][j] < dist[j]) {
				dist[j] = adj[vnear][j];
			}
		}
	}
}

int main() {
	// init adj, dist
	for (int i = 0; i < MAX_VERTICES + 1; i++) {
		dist[i] = INT_MAX;
		for (int j = 0; j < MAX_VERTICES + 1; j++) {
			adj[i][j] = INT_MAX;
		}
	}
	// adj[i][j] 값 넣어주기

	prim();

	return 0;
}
```   
</br>

***
## 크루스칼 알고리즘 (Kruskal's Algorithm)
가중치가 작은 간선(edge)를 선택해가며 최소비용 신장트리를 만드는 방법.   
매 선택마다 가장 좋아보이는 것을 선택하기 때문에 탐욕 알고리즘(Greedy Algorithm) 이다.
### 그래프 G=(V, E)의 최소비용 신장트리 T=(Y, F)를 만드는 과정
1. 각 정점(vertex)들을 자기자신만 포함하는 서로소 부분집합으로 만드는 걸로 시작한다.
2. 가중치가 작은 간선(edge)부터 선택한다. 만약 가중치가 같으면 임의로 선택한다.
3. 만약 선택한 간선(edge)이 서로소 부분집합들에 있는 두 정점(vertex)를 연결하면, 그 간선을 F에 추가하고 두 부분집합을 하나로 합친다.

이 절차를 의사코드로 나타내면 다음과 같다.
```
V의 정점들을 자기 자신만 포함한 서로소 부분집합으로 구축;
F = {};

while (!(모든 부분집합이 하나로 합쳐짐)) {
    E - F 에 속한 간선중 가장 가중치가 작은 간선 선택;

    if(선택한 간선이 서로소인 부분집합의 두 마디를 연결함) {
        부분집합을 합침;
        그 간선(edge)를 F에 추가;
    }
}
```

다음 그림으로 프림 알고리즘이 어떻게 실행되는지 알 수 있다.   
![ANY_0105213133](https://user-images.githubusercontent.com/44018094/103646729-7a955980-4f9d-11eb-860c-32e94fd835d4.gif)
