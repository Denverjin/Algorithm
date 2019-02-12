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
int n;
string s;
string t;
int nxt[N][26];
int cnt;
int val[N];
int fail[N];
queue <int> que;

void ins() {
	int i, u;
	for (i = 0, u = 0; i < s.size(); ++ i) {
		if (!nxt[u][s[i] - 'a']) nxt[u][s[i] - 'a'] = ++ cnt;
		u = nxt[u][s[i] - 'a'];
	}
	val[u] ++;
}

void build() {
	for (int i = 0; i < 26; ++ i) {
		if (nxt[0][i]) {
			que.push(nxt[0][i]);
			fail[nxt[0][i]] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = 0; i < 26; ++ i) {
			if (nxt[u][i]) {
				fail[nxt[u][i]] = nxt[fail[u]][i];
				que.push(nxt[u][i]);
			}
			else {
				nxt[u][i] = nxt[fail[u]][i];
			}
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		cin >> s;
		ins();
	}
	build();
	cin >> t;
	int u = 0, ans = 0;
	for (int i = 0; i < t.size(); ++ i) {
		u = nxt[u][t[i] - 'a'];
		ans += val[u];
		val[u] = 0;
	}
	printf("%d\n", ans);
	return 0;
}

