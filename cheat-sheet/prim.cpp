#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
using namespace std;

#define MAX_VERTICES 1000

int adj[MAX_VERTICES + 1][MAX_VERTICES + 1];	// 인접행렬
int isVisit[MAX_VERTICES + 1];					// 이 vertex가  MST = (Y, F)의 Y(vertices 집합)에 포함됐는지 여부
int dist[MAX_VERTICES + 1];						// 이 vertex와 Y와의 최소거리. (이미 포함된 경우 0)
int nVerteices;									// vertex 개수

void prim() {
	dist[1] = 0;										// V1부터 시작
	isVisit[1] = true;									// V1이 Y에 포함됨
	for (int i = 2; i <= nVerteices; i++) {
		if (dist[i] > adj[1][i]) dist[i] = adj[1][i];	// V1과 인접해있는 vertex들의 distance를 adj[1][vertexIndex]로 갱신
	}

	for (int i = 0; i < nVerteices - 1; i++) {			// V1은 이미 Y에 포함됐으므로 N - 1번 반복
		// G = (V, E)의 V - Y 중에서 Y와 가장 가까운 vertex 찾기
		int minDist = INT_MAX;							// 가장 가까운 vertex와의 거리
		int vnear;										// 가장 가까운 vertex의 index
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

