// Code by Denverjin.
#include <bits/stdc++.h>
using namespace std;

#define ld double
#define ll long long
#define pii pair <int, int>
#define ull unsigned long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i, n) for (int i = 0; i < (int)(n); ++ i)

#define PI acos(-1)
#define MOD 1000000007
#define MUL 19260817
#define EPS 1e-10
#define INF 1e9
#define LINF 1e18

template <typename T> inline void chkmin(T &x, T y) {if (y < x) x = y;}
template <typename T> inline void chkmax(T &x, T y) {if (y > x) x = y;}
template <typename T> inline T add(T x, T y) {return (x + y) % MOD;}
template <typename T> inline T mul(T x, T y) {return 1LL * x * y % MOD;}
template <typename T> inline T qp(T x, T n) {
	T ans = 1;
	do {if (n & 1) ans = mul(ans, x); x = mul(x, x);} while (n >>= 1);
	return ans;
}

#ifndef DEBUG
const int SZ = 1 << 13;
char buff[SZ], *pos = buff + SZ - 1;
#define getchar() (++ pos == buff + SZ ? fread(pos = buff, 1, SZ, stdin), *pos : *pos)
#endif

inline ll read() {
	ll x = 0; int f = 1, c = getchar();
	for (;!isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x<<3) + (x<<1) + (c^48);
	return x * f;
}

namespace SAM {
	static const int N = 1 << 22;
	int tot, lst, go[N][26], link[N], len[N], tms[N];
	void init() {
		tot = lst = 1;
		memset(go, 0, sizeof go);
	}
	void add(int c) {
		int p = lst, np = ++ tot; lst = np;
		len[np] = len[p] + 1;
		while (p && !go[p][c]) go[p][c] = np, p = link[p];
		if (!p) link[np] = 1;
		else {
			int q = go[p][c];
			if (len[q] == len[p] + 1) link[np] = q;
			else {
				int nq = ++ tot;
				len[nq] = len[p] + 1; link[nq] = link[q];
				memcpy(go[nq], go[q], sizeof go[q]);
				link[np] = link[q] = nq;
				while (go[p][c] == q) go[p][c] = nq, p = link[p];
			}
		}
//		printf("%d\n", np);
		tms[np] = 1;
	}
}

int cnt[SAM :: N], v[SAM :: N];

int main() {
	SAM :: init();
	char c = getchar();
	while (!isspace(c)) {
		SAM :: add(c - 'a');
		c = getchar();
	}
//	for (int i = 1; i <= SAM :: tot; ++ i) {
//		printf("%d: ", i);
//		rep(j, 26) printf("%d ", SAM :: go[i][j]);
//		printf("link: %d\n", SAM :: link[i]);
//	}
	ll ans = 0;
	for (int i = 1; i <= SAM :: tot; ++ i) cnt[SAM :: len[i]] ++;
	for (int i = 1; i < SAM :: N; ++ i) cnt[i] += cnt[i - 1];
	for (int i = SAM :: tot; i; -- i) v[cnt[SAM :: len[i]] --] = i;
	for (int i = SAM :: tot; i; -- i) {
		int p = v[i];
		SAM :: tms[SAM :: link[p]] += SAM :: tms[p];
		if (SAM :: tms[p] > 1) chkmax(ans, 1LL * SAM :: tms[p] * SAM :: len[p]);
	}
	printf("%lld\n", ans);
	return 0;
}

