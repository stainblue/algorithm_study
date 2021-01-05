// 에라토스테네스의 체
// https://ko.wikipedia.org/wiki/%EC%97%90%EB%9D%BC%ED%86%A0%EC%8A%A4%ED%85%8C%EB%84%A4%EC%8A%A4%EC%9D%98_%EC%B2%B4

#include <iostream>
#include <string.h>
using namespace std;

#define MAX 1000

int main() {
	// 1000 이하의 소수 구하기
	bool isprime[MAX + 1];
	memset(isprime, true, sizeof(isprime));

	isprime[0] = isprime[1] = false;
	for (int i = 2; i <= MAX; i++) {
		if (!isprime[i]) continue;

		for (int j = i * 2; j <= MAX; j += i) {
			isprime[j] = false;
		}
	}
}
