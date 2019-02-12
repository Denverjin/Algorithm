// Code by Denverjin.
#include <bits/stdc++.h>
using namespace std;

using ld = double;
using ll = long long;
using ull = unsigned long long;
const int INF = 1 << 30;
const ll LINF = 1LL << 60;

const int SZ = 1 << 13;
char buff[SZ], *pos = buff + SZ - 1;
#define getchar() (++ pos == buff + SZ ? fread(pos = buff, 1, SZ, stdin), *pos : *pos)

inline ll read() {
	ll x = 0; int f = 1, c = getchar();
	for (;!isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x<<3) + (x<<1) + (c^48);
	return x * f;
}

const int N = 1 << 20;
string s, t;
int n, m;
int fail[N];

int main() {
	cin >> s >> t;
	n = s.size();
	m = t.size();
	for (int i = 0, j = fail[0] = -1; i < m; ++ i) {
		while (~j && t[j] != t[i]) j = fail[j];
		fail[i + 1] = ++ j;
	}
	for (int i = 0, j = 0; i < n; ++ i) {
		while (~j && t[j] != s[i]) j = fail[j];
		++ j;
		if (j == m) printf("%d\n", i - m + 2);
	}
	for (int i = 0; i < m; ++ i) printf("%d ", fail[i + 1]);
	return 0;
}

