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

const int N = 1 << 20;

queue <int> freenodes;
int newnode() {int x = freenodes.front(); freenodes.pop(); return x;}
struct Node {int fa, ch[2], val, rev, sz; Node() {fa = ch[0] = ch[1] = val = rev = 0; sz = 1;}} node[N];
void init() {rep(i, N) if (i) freenodes.push(i);}

void pushdown(int x) {
    if (node[x].rev) {
        node[x].rev = 0;
        if (node[x].ch[0]) node[node[x].ch[0]].rev ^= 1;
        if (node[x].ch[1]) node[node[x].ch[1]].rev ^= 1;
        swap(node[x].ch[0], node[x].ch[1]);
    }
}

void pushup(int x) {
    node[x].sz = node[node[x].ch[0]].sz + 1 + node[node[x].ch[1]].sz;
}

void rotate(int x, int &t) {
    int y = node[x].fa, z = node[y].fa;
    int tp = node[y].ch[1] == x;
    if (y == t) t = x;
    else node[z].ch[node[z].ch[1] == y] = x;
    node[x].fa = z; node[y].fa = x;
    node[y].ch[tp] = node[x].ch[tp ^ 1];
    node[node[y].ch[tp]].fa = y;
    node[x].ch[tp ^ 1] = y;
    pushup(x); if (y) pushup(y); if (z) pushup(z);
}

void splay(int x, int &t) {
    while (x != t) {
        int y = node[x].fa, z = node[y].fa;
        if (y != t) rotate((node[z].ch[1] == y) ^ (node[y].ch[1] == x) ? x : y, t);
        rotate(x, t);
    }
}

int build(int l, int r) {
    if (l >= r) return 0;
    int x = newnode();
    int md = (l + r) >> 1;
    node[x].val = md;
    int L = build(l, md);
    int R = build(md + 1, r);
    node[x].ch[0] = L; if (L) node[L].fa = x;
    node[x].ch[1] = R; if (R) node[R].fa = x;
    pushup(x);
    return x;
}

int find(int x, int k) {
//	printf("%d %d\n", x, k);
    pushdown(x);
    int szz = node[node[x].ch[0]].sz;
    if (szz + 1 == k) return x;
    else if (szz + 1 < k) return find(node[x].ch[1], k - szz - 1);
    else return find(node[x].ch[0], k);
}

void dbg(int x) {
    if (!x) return;
    dbg(node[x].ch[0]);
    printf("%d ", node[x].val);
    dbg(node[x].ch[1]);
}

int main() {
    node[0].sz = 0;
    init();
    int n = read(), q = read();
    int rt = build(0, n + 2);
//	dbg(rt); puts("");
    rep(i, q) {
        int l = read(), r = read();
        int L = find(rt, l), R = find(rt, r + 2);
        splay(L, rt);
        splay(R, node[rt].ch[1]);
        node[node[R].ch[0]].rev ^= 1;
//		dbg(rt); puts("");
    }
//	dbg(rt); puts("");
    for (int i = 1; i <= n; ++ i)
        printf("%d ", node[find(rt, i + 1)].val);
    return 0;
}

