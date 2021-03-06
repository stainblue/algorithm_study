# LIS (가장 긴 증가하는 부분 수열)

## 목차
1. LIS 란?
2. LIS의 길이를 구하는 알고리즘
3. LIS의 길이를 구하는 더 빠른 알고리즘
    

## 1. LIS 란?
LIS 는 Longest Increasing Subsequence 의 약자로 한국어로 **가장 긴 증가하는 부분 수열** 정도로 해석할 수 있다.   
이는 어떤 수열이 주어질 때, 이 수열에서 몇 개의 수들을 제거하여 만들어낼 수 있는 **증가 부분 수열 (increasing subsequence) 중 가장 길이가 긴 수열**을 말한다. 이때 만들어진 수열의 숫자들은 **주어진 수열에서 위치가 이어져 있지 않아도 된다.**   
</br>
예를 들어 다음과 같은 수열이 주어졌다고 하자.   
`[1 2 1 3 5]`   

이 수열에서 몇 개의 수들을 제거하여 다음과 같은 부분 수열을 만들어낼 수 있다.   
`[1 2]`   
`[1 1 3]`   
`[2 1 3 5]`   
`[1 2 3 5]`   

여기서 첫번재와 네번째 수열은 **오름차순**으로 정렬되어있다. 이를 **증가 부분 수열**이라 하고, 증가 부분 수열중 가장 길이가 긴 수열, 즉 **`[1 2 3 5]` 가 LIS**가 된다.

**LIS는 여러개가 나올 수 있다.**    
예를들어 `[2 3 1 2 4]` 의 부분 수열 `[2 3 4]`와 `[1 2 4]`는 모두 길이가 3인 LIS이다.

## 2. LIS의 길이를 구하는 알고리즘
길이가 N인 임의의 수열의 LIS 길이를 구해야 하는 문제를 해결할 수 있는 알고리즘이다.   
문제 : [가장 긴 증가하는 부분 수열 (백준 11053)](https://www.acmicpc.net/problem/11053)

### 2-1. 완전탐색을 이용한 풀이
* 주어진 수열을 처음부터 탐색하며 모든 경우의 수 (가능한 모든 증가 부분 수열) 을 구해보는 방법을 생각해 볼 수 있다.   
주어진 수열을 **`A`** 라고 하면 **`A[i]` 가 마지막인 증가 부분 수열의 길이**는 **`j < i && A[j] < A[i]`** 인 **`j`** 가 존재할 때 **`A[j]` 가 마지막인 증가 부분 수열의 길이 + 1** 이 된다.

* 재귀를 사용하여 이를 구현한 코드는 다음과 같다.
```c++
#include <iostream>
using namespace std;

#define endl "\n"
#define ll long long

int N, A[1001];

int getLISlen(int i) {
	int ans = 1;
	for (int j = 1; j < i; j++) {
		if (!(A[j] < A[i])) continue;
		ans = max(ans, getLISlen(j) + 1);
	}
	return ans;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	
	cin >> N;
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		ans = max(ans, getLISlen(i));
	}
	cout << ans << endl;
	
	return 0;
}
```

* 시간 복잡도 : N 이 1 커지면 `getLISlen()` 함수가 2배로 호출된다. 즉, 시간복잡도는 **O(2<sup>N</sup>)** 이다. 아래 그림은 함수가 호출되는 모습을 나타낸 그림이다.   

***
**N 이 3 일때**
![N 이 3 일때](https://user-images.githubusercontent.com/44018094/110198511-75b62e80-7e96-11eb-9271-1c645c44fed7.png)   
***
**N 이 4 일때**
![N 이 4 일때](https://user-images.githubusercontent.com/44018094/110198514-764ec500-7e96-11eb-892b-e9660f44eaba.png)   
***
이 문제의 경우 N 의 범위가 1 ~ 1000 이기 때문에 위 풀이로는 시간초과가 난다.


### 2-2. DP를 이용한 풀이

### 2-3. 이분탐색을 이용한 풀이