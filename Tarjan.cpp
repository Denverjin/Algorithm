// Code by Denverjin.
#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;

const int SZ = 1 << 13;
char buff[SZ], *pos = buff + SZ - 1;
#define getchar() (++ pos == buff + SZ ? fread(pos = buff, 1, SZ, stdin), *pos : *pos)

inline int read() {
	int x = 0; int f = 1, c = getchar();
	for (;!isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x<<3) + (x<<1) + (c^48);
	return x * f;
}

const int N = 1 << 20;
vector <int> g[N], ng[N];
int n, m;
int dfn[N], low[N], T;
int stk[N], tp, instk[N];
int cc[N], ccc;
int sz[N], Sz[N];
int vis[N];

void dfs(int u) {
	instk[u] = 1;
	stk[++ tp] = u;
	dfn[u] = low[u] = ++ T;
	for (int i = 0; i < g[u].size(); ++ i) {
		int v = g[u][i];
		if (!dfn[v]) {
			dfs(v);
			if (low[v] < low[u]) low[u] = low[v];
		}
		else if (instk[v]) {
			if (dfn[v] < low[u]) low[u] = dfn[v];
		}
	}
	if (dfn[u] == low[u]) {
		++ ccc;
		while (tp) {
			cc[stk[tp]] = ccc;
			instk[stk[tp]] = 0;
			-- tp;
			if (stk[tp + 1] == u) break;
		}
	}
}

int main() {
	n = read(), m = read();
	while (m --) {
		int u = read() - 1, v = read() - 1;
		g[u].push_back(v);
	}
	for (int i = 0; i < n; ++ i) if (!dfn[i]) dfs(i);
	return 0;
}

