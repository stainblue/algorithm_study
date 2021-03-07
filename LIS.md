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
주어진 수열을 처음부터 탐색하며 모든 경우의 수 (가능한 모든 증가 부분 수열) 을 구해보는 방법을 생각해 볼 수 있다.   
주어진 수열을 **`A`** 라고 하면 **`A[i]` 가 마지막인 증가 부분 수열의 길이**는 **`j < i && A[j] < A[i]`** 인 **`j`** 가 존재할 때 **`A[j]` 가 마지막인 증가 부분 수열의 길이 + 1** 이 된다.

재귀를 사용하여 이를 구현한 코드는 다음과 같다.
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

**시간 복잡도** : N 이 1 커지면 `getLISlen()` 함수가 2배로 호출된다. 즉, 시간복잡도는 **O(2<sup>N</sup>)** 이다. 아래 그림은 함수가 호출되는 모습을 나타낸 그림이다.   

***
**N 이 3 일때**
![N 이 3 일때](https://user-images.githubusercontent.com/44018094/110198511-75b62e80-7e96-11eb-9271-1c645c44fed7.png)   
***
**N 이 4 일때**
![N 이 4 일때](https://user-images.githubusercontent.com/44018094/110198514-764ec500-7e96-11eb-892b-e9660f44eaba.png)   
***
이 문제의 경우 N 의 범위가 1 ~ 1000 이기 때문에 위 풀이로는 시간초과가 난다.


### 2-2. DP를 이용한 풀이
완전탐색 해법의 아이디어와 동일하지만, 메모이제이션(`A[i] 을 마지막으로 하는 가장 긴 증가 부분 수열의 길이를 어딘가에 저장`) 을 통해 시간을 획기적으로 줄일 수 있다.   
Top down 과 Bottom up 모두 가능하지만 여기서는 좀 더 대중적이고 편리하고 빠르기까지 한 Bottom up 으로 풀어보겠다.

새로운 배열 **`length[i]`를 `A[i]`가 마지막인 가장 긴 부분 증가 수열의 길이** 라고 하자.
**`A[i]`** 가 어떤 증가 부분 수열의 마지막 숫자가 되려면 **`A[i]` 가 추가되기 전 증가 부분 수열의 마지막 값보다 커야한다.** 

따라서, **`length[i]`의 값은 `A[i]` 가 추가될 수 있는 증가 부분 수열중 가장 길이가 긴 수열의 길이에 1을 더한 값이다.**

이후 `length`의 값을 모두 조회하여 얻어낸 가장 큰 값이 LIS가 된다.

상세한 진행 방식을 그림과 함께 알아보자.   
</br>

***
![그림1](https://user-images.githubusercontent.com/44018094/110199432-b795a380-7e9b-11eb-9805-0754a20b1496.png)   
배열 `length`의 기본값은 모두 1이다. 이는 각 숫자를 마지막으로 하는 가장 긴 부분 수열의 길이은 적어도 1 이상이라는 의미이다.   

</br>

***
![그림2](https://user-images.githubusercontent.com/44018094/110199433-b82e3a00-7e9b-11eb-9b21-68432dba153e.png)   
**i**가 1 일때,   
`A[1]`은 첫번째 원소이므로 `A[1]`를 마지막으로 하는 가장 긴 부분 증가 수열의 길이는 1이다.   

</br>

***
![그림3](https://user-images.githubusercontent.com/44018094/110199434-b8c6d080-7e9b-11eb-819e-d72be8347504.png)   
**i**가 2일때,   
`A[1] < A[2]` 이고 현재 `length[2]`보다 `length[1] + 1` 이 더 크므로 `length[2] = length[1] + 1` 해준다. (`length[2] = max(length[2], length[1] + 1)`)   

</br>

***
![그림4](https://user-images.githubusercontent.com/44018094/110199436-b8c6d080-7e9b-11eb-8308-af82da68080b.png)   
**i**가 3일때,   
`A[1]`이 `A[3]`보다 작지 않으므로 그냥 넘어간다.   

</br>

***
![그림5](https://user-images.githubusercontent.com/44018094/110199437-b95f6700-7e9b-11eb-9a84-09ba5daacdb7.png)   
마찬가지로 `A[2]`이 `A[3]`보다 작지 않으므로 그냥 넘어간다.   

</br>

***
![그림6](https://user-images.githubusercontent.com/44018094/110199438-b95f6700-7e9b-11eb-9917-180419b87e31.png)   
**i**가 4일때,   
`A[1] < A[4] && length[4] < length[1] + 1` 이므로 `length[4] = length[1] + 1`

</br>

***
![그림7](https://user-images.githubusercontent.com/44018094/110199439-b9f7fd80-7e9b-11eb-946c-efe22de16d46.png)   
`A[2] < A[4] && length[4] < length[2] + 1` 이므로 `length[4] = length[2] + 1`

</br>

***
![그림8](https://user-images.githubusercontent.com/44018094/110199440-b9f7fd80-7e9b-11eb-99d8-dc3ce1f6d943.png)   
`A[3] < A[4]` 이지만, `length[4] >= length[3] + 1` 이므로 그냥 넘어간다.

</br>

***
![그림9](https://user-images.githubusercontent.com/44018094/110199441-ba909400-7e9b-11eb-846c-6d15999be3bc.png)   
**i**가 5일때,   
`A[1] < A[5] && length[5] < length[1] + 1` 이므로 `length[5] = length[1] + 1`

</br>

***
![그림10](https://user-images.githubusercontent.com/44018094/110199442-ba909400-7e9b-11eb-90a6-d778b90d991a.png)   
`A[2] < A[5] && length[5] < length[2] + 1` 이므로 `length[5] = length[2] + 1`

</br>

***
![그림11](https://user-images.githubusercontent.com/44018094/110199443-bb292a80-7e9b-11eb-982a-c3f15a1f827c.png)   
`A[3] < A[5]` 이지만 `length[5] >= length[3] + 1` 이므로 그냥 넘어간다.

</br>

***
![그림12](https://user-images.githubusercontent.com/44018094/110199444-bb292a80-7e9b-11eb-8fb8-386a12deccf6.png)   
`A[4] < A[5] && length[5] < length[4] + 1` 이므로 `length[5] = length[4] + 1`

***

</br>

이를 구현한 코드는 다음과 같다.
```c++
#include <iostream>
using namespace std;

int N;
int A[1001];
int length[1001];

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		length[i] = 1;
		for (int j = 1; j < i; j++) {
			if (A[j] < A[i]) length[i] = max(length[i], length[j] + 1);
		}
		ans = max(ans, length[i]);
	}

	cout << ans << endl;

	return 0;
}
```

**시간 복잡도** : 매 `i` 마다 `1 ~ i - 1` 까지 반복하며 `length` 배열을 갱신하므로 **O(N<sup>2</sup>)** 이다.

### 2-3. 이분탐색을 이용한 풀이