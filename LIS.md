# LIS (가장 긴 증가하는 부분 수열)

## 목차
1. LIS 란?
2. LIS의 길이를 구하는 알고리즘   
	2-1. 완전탐색을 이용한 풀이   
	2-2. DP를 이용한 풀이   
	2-3. 이분탐색을 이용한 풀이
    

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

N이 1000이하인 이 문제에서는 이 풀이로 해결할 수 있다. 하지만, N이 10만이 넘어가는 문제에서는 시간초과가 나게된다.

### 2-3. 이분탐색을 이용한 풀이
[가장 긴 증가하는 부분 수열 3 (백준 12738)](https://www.acmicpc.net/problem/12738) 과 같이 N이 큰 경우에는 O(N<sup>2</sup>)의 시간복잡도로 문제를 해결할 수 없다. 이를 개선하기 위한 방법으로 **세그먼트 트리**를 사용하는 방법과 **이분탐색**을 사용하는 방법이 있다. 여기서는 비교적 간단한 **이분탐색**을 이용한 방법을 소개하겠다.      

이전 알고리즘에서 `length[i]`를 구하기 위해 `A[i]`와 `A[1] ~ A[i - 1]`를 비교한 이유는 `i > j && A[i] > A[j]`를 만족하는 `j`중에서 가장 큰 `length[j]`값을 구하기 위함이다. **만약 i번째 이전 가장 큰 `length`의 값을 갖는 `j`중 가장 작은 `A[j]`값을 리스트로 관리한다면, `length[i]`를 구하기 위해 리스트와 `A[i]`를 비교하기만 하면 된다.**

배열 X를 다음과 같이 정의하자.   
**`X[i] = 길이가 i인 부분 증가 수열중 가장 작은 마지막 숫자`**    
그리고 배열 X의 마지막 값과 인덱스를 **last**, **lastIdx**라 하자. 그럼 주어진 수열을 순회하며 배열 X를 채워나갈 때 다음과 같은 규칙을 따르게 된다.   
```
if (A[i] > last)
	X[lastIdx + 1] = A[i];
else
	X[j] = A[i]; 	// X[j - 1] < A[i] <= X[j]
```   
배열 X는 오름차순으로 정렬되어 있기 때문에, 새 숫자를 넣을 때 이분탐색을 통해 빠르게 적합한 위치를 찾아줄 수 있다.   
자세한 진행방식은 다음과 같다.   

***
![그림1](https://user-images.githubusercontent.com/44018094/110244630-f95d4180-7fa2-11eb-8c66-f3b82ec3a2fb.png)   
처음 배열 X는 아무것도 없이 비워져있다.

</br>

***
![그림2](https://user-images.githubusercontent.com/44018094/110244631-f9f5d800-7fa2-11eb-9371-4bb462b58531.png)   
`i == 1`일 때,   
X가 비어있기 때문에 X 끝에 10을 넣어준다.   

이는 길이가 1인 부분 증가 수열 중에서 가장 작은 마지막 숫자가 10이라는 뜻이다.

</br>

***
![그림3](https://user-images.githubusercontent.com/44018094/110244632-fa8e6e80-7fa2-11eb-8729-5821c3c4214b.png)   
`i == 2`일 때,   
20(`A[2]`)은 X의 마지막 값(10)보다 크므로 X 끝에 20을 넣어준다.   

이는 i이전까지의 가장 긴 부분 증가 수열의 마지막 값 보다 20이 크기 때문에 여기에 20을 추가하여 더 긴 부분 증가 수열을 만들 수 있다는 의미이다.   

</br>

***
![그림4](https://user-images.githubusercontent.com/44018094/110244633-fa8e6e80-7fa2-11eb-8008-9ee668f92381.png)   
`i == 3`일 때,   
5(`A[3]`)은 X의 마지막 값(20)보다 작다.   
X에 5가 들어갈 자리를 생각해 보면 5는 길이가 0인 부분 증가 수열의 마지막 값(표기되어있지는 않지만 음의 무한대라고 가정) 보단 크고, 길이가 1인 부분 증가 수열의 마지막 값(10) 보다는 작다. 따라서, `X[1]`의 값을 5로 바꿔준다.   

이는 원래 수열을 3번째까지 봤을 때 길이가 1인 가장 긴 부분 증가 수열의 가장 작은 마지막 값이 5이고, 따라서 이후에 5보다 큰 수가 나오면 여기에 더하여 길이가 2이상인 부분 증가 수열을 만들 수 있다는 뜻이다.

</br>

***
![그림5](https://user-images.githubusercontent.com/44018094/110244634-fb270500-7fa2-11eb-9cb0-c09d854ef08e.png)   
`i == 4`일 때,   
30(`A[4]`)은 X의 마지막 값(20)보다 크므로 X 끝에 30을 넣어준다.

</br>

***
![그림6](https://user-images.githubusercontent.com/44018094/110244636-fb270500-7fa2-11eb-9dab-9e0a2b5382e6.png)   
`i == 5`일 때,   
50(`A[5]`)은 X의 마지막 값(30)보다 크므로 X 끝에 50을 넣어준다.

***


이를 구현한 코드는 다음과 같다.
```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define endl "\n"
const int INF = 2'100'000'000;
int N;

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;
	vector<int> x;
	v.push_back(-INF); // 길이가 0인 부분증가수열의 가장 작은 마지막 수를 지정해준다.
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		int k;
		cin >> k;
		if (x.back() < k) {
			x.push_back(k);
			ans++;
		}
		else {
			// x는 오름차순으로 정렬되어 있다.
			// x에 k가 들어갈 자리를 이분탐색으로 찾는다.
			vector<int>::iterator it = lower_bound(x.begin(), x.end(), k);
			*it = k;
		}
	}

	cout << ans << endl;
	return 0;
}
```   

**시간 복잡도** : x가 오름차순으로 정렬되어 있기 때문에, 새로운 숫자를 넣을 때 이분탐색으로 검색을 할 수 있었다. 이분탐색에는 O(logN)의 시간복잡도가 필요하고, N개의 숫자마다 x를 이분탐색하기 때문에 총 시간복잡도는 **O(NlogN)** 이다.

주의할 점 : 배열 X는 LIS의 길이를 구하기 위해 사용하는 배열이지 X의 요소들이 LIS는 아니다. 예를들어 주어진 수열이 `[2 3 4 5 1]`인 경우 LIS는 `[2 3 4 5]`이지만 수열을 끝까지 확인한 뒤의 X에는 `[1 3 4 5]`가 들어 있을것이다.