#include <iostream>
#include <string>
using namespace std;

#define MAXLEN 1000000

class KMP {
private:
	string S, P;
	int failFunction[MAXLEN] = { 0 };
	void makeFailFunction() {
		int i, j = 0, np = P.length();
		for (i = 1; i < np; i++) {
			while (j > 0 && P[i] != P[j])
				j = failFunction[j - 1];

			if (P[i] == P[j])
				failFunction[i] = ++j;
		}
	}
public:
	KMP(const string& s, const string& p) {
		S = s;
		P = p;
		makeFailFunction();
	}

	void sol() {
		int i, j = 0, ns = S.length(), np = P.length();
		for (i = 0; i < ns; i++) {
			while (j > 0 && S[i] != P[j]) 
				j = failFunction[j - 1];

			if (S[i] == P[j]) 
				j++;

			if (j >= np) {
				// Found P in S
				return;
			}
		}
	}
};
