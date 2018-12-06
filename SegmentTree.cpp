#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1 << 17;

int n, q;
ll a[N];

struct SEGT {
	int sz;
	ll add[N + N], sum[N + N];

	void build() {
		memset(add, 0, sizeof add);
		memset(sum, 0, sizeof sum);
		for (sz = 1; sz <= n; sz <<= 1);
		for (int i = 0; i < n; ++ i) sum[i + sz] = a[i];
		for (int i = sz - 1; ~i; -- i) sum[i] = sum[i << 1] + sum[i << 1 | 1];
	}

	void pushdown(int i, int len) {
		if (add[i]) {
			sum[i] += add[i] * len;
			if (i < sz) {
				add[i << 1] += add[i];
				add[i << 1 | 1] += add[i];
			}
			add[i] = 0;
		}
	}

	void upd(int a, int b, int i, int l, int r, ll v) {
		pushdown(i, b - a);
		if (l <= a && b <= r) {
			add[i] += v, pushdown(i, b - a);
			return;
		}
		if (r <= a || b <= l) return;
		upd(a, (a + b) >> 1, i << 1, l, r, v);
		upd((a + b) >> 1, b, i << 1 | 1, l, r, v);
		sum[i] = sum[i << 1] + sum[i << 1 | 1];
	}

	void upd(int l, int r, ll v) {
		upd(0, sz, 1, l - 1, r, v);
	}

	ll qry(int a, int b, int i, int l, int r) {
		pushdown(i, b - a);
		if (l <= a && b <= r) return sum[i];
		if (r <= a || b <= l) return 0;
		ll L = qry(a, (a + b) >> 1, i << 1, l, r);
		ll R = qry((a + b) >> 1, b, i << 1 | 1, l, r);
		return L + R;
	}

	ll qry(int l, int r) {
		return qry(0, sz, 1, l - 1, r);
	}
} segt;

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++ i) scanf("%lld", &a[i]);

	segt.build();

	while (q --) {
		int tp, l, r; scanf("%d%d%d", &tp, &l, &r);
		if (tp == 1) {
			int v; scanf("%d", &v);
			segt.upd(l, r, v);
		}
		else {
			printf("%lld\n", segt.qry(l, r));
		}
	}

	return 0;
}
