#include <cstdio>
#include <cstring>

const int N = 1 << 21;

int n;
char s[N];
int sa[N], rnk[N];
int c[N];
int v[N], tmp[N];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++ i) ++ c[s[i]];
	for (int i = 1; i < 128; ++ i) c[i] += c[i - 1];
	for (int i = n; i; -- i) sa[c[s[i]] --] = i;
	rnk[sa[1]] = 1;
	for (int i = 2; i <= n; ++ i)
		rnk[sa[i]] = rnk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
	for (int i = 1; i < n; i <<= 1) {
		int mxrnk = rnk[sa[n]], k = 0;
		for (int j = n; j > n - i; -- j) v[++ k] = j;
		for (int j = 1; j <= n; ++ j) if (sa[j] > i) v[++ k] = sa[j] - i;
		memset(c, 0, sizeof c);
		for (int j = 1; j <= n; ++ j) ++ c[rnk[v[j]]];
		for (int j = 1; j <= mxrnk; ++ j) c[j] += c[j - 1];
		for (int j = n; j; -- j) sa[c[rnk[v[j]]] --] = v[j];
		for (int j = 1; j <= n; ++ j) tmp[j] = rnk[j];
		rnk[sa[1]] = 1;
		for (int j = 2; j <= n; ++ j)
			rnk[sa[j]] = rnk[sa[j - 1]] + (tmp[sa[j]] != tmp[sa[j - 1]] || tmp[sa[j] + i] != tmp[sa[j - 1] + i]);
	}
	for (int i = 1; i <= n; ++ i) printf("%d ", sa[i]);
	return 0;
}

