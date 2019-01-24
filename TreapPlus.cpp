#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1 << 20;
const int INF = 1 << 30;

namespace Treap {
	struct Node {
		int sz;
		ll sum, maxprv, maxsuf, maxsum, fix, val, rev, lazy;
		Node *l, *r;
	} nodes[N];
	Node* root;
	queue <Node*> freenodes;

	void init() {
		for (int i = 0; i < N; ++ i) freenodes.push(&nodes[i]);
		root = NULL;
	}

	Node* newnode(int val) {
		Node *x = freenodes.front();
		freenodes.pop();
		x -> sz = 1;
		x -> fix = rand();
		x -> val = val;
		x -> rev = 0;
		x -> lazy = -INF;
		x -> sum = x -> maxsum = val;
		x -> maxprv = x -> maxsuf = max(val, 0); 
		x -> l = x -> r = NULL;
		return x;
	}

	void freenode(Node *x) {
		freenodes.push(x);
	}

	void freetreap(Node *x) {
		if (!x) return;
		freetreap(x -> l);
		freetreap(x -> r);
		freenode(x);
	}

	void pushdown(Node *x) {
		if (x -> rev) {
			if (x -> l) {
				x -> l -> rev ^= 1;
				swap(x -> l -> l, x -> l -> r);
				swap(x -> l -> maxprv, x -> l -> maxsuf);
			}
			if (x -> r) {
				x -> r -> rev ^= 1;
				swap(x -> r -> l, x -> r -> r);
				swap(x -> r -> maxprv, x -> r -> maxsuf);
			}
			x -> rev = 0;
		}
		if (x -> lazy != -INF) {
			if (x -> l) {
				x -> l -> val = x -> lazy;
				x -> l -> lazy = x -> lazy;
				x -> l -> sum = x -> lazy * x -> l -> sz;
				x -> l -> maxprv = x -> l -> maxsuf = max(0LL, x -> l -> sum);
				x -> l -> maxsum = max(x -> l -> sum, x -> lazy);
			}
			if (x -> r) {
				x -> r -> val = x -> lazy;
				x -> r -> lazy = x -> lazy;
				x -> r -> sum = x -> lazy * x -> r -> sz;
				x -> r -> maxprv = x -> r -> maxsuf = max(0LL, x -> r -> sum);
				x -> r -> maxsum = max(x -> r -> sum, x -> lazy);
			}
			x -> lazy = -INF;
		}
	}

	void pushup(Node *x) {
		x -> sz = 1;
		if (x -> l) x -> sz += x -> l -> sz;
		if (x -> r) x -> sz += x -> r -> sz;
		x -> sum = x -> val;
		if (x -> l) x -> sum += x -> l -> sum;
		if (x -> r) x -> sum += x -> r -> sum;
		x -> maxprv = 0LL;
		if (x -> l) {
			x -> maxprv = max(x -> l -> sum + x -> val, x -> l -> maxprv);
			if (x -> r)
				x -> maxprv = max(x -> maxprv, x -> l -> sum + x -> val + x -> r -> maxprv);
		}
		else {
			x -> maxprv = x -> val;
			if (x -> r) x -> maxprv += x -> r -> maxprv;
			x -> maxprv = max(x -> maxprv, 0LL);
		}
		x -> maxsuf = 0LL;
		if (x -> r) {
			x -> maxsuf = max(x -> r -> sum + x -> val, x -> r -> maxsuf);
			if (x -> l)
				x -> maxsuf = max(x -> maxsuf, x -> r -> sum + x -> val + x -> l -> maxsuf);
		}
		else {
			x -> maxsuf = x -> val;
			if (x -> l) x -> maxsuf += x -> l -> maxsuf;
			x -> maxsuf = max(x -> maxsuf, 0LL);
		}
		x -> maxsum = x -> val;
		if (x -> l) x -> maxsum += x -> l -> maxsuf;
		if (x -> r) x -> maxsum += x -> r -> maxprv;
		if (x -> l) x -> maxsum = max(x -> maxsum, x -> l -> maxsum);
		if (x -> r) x -> maxsum = max(x -> maxsum, x -> r -> maxsum);
	}

	void split(Node *x, int k, Node *&l, Node *&r) {
		if (!x) {
			l = r = NULL;
			return;
		}
		pushdown(x);
		int lsz = x -> l ? x -> l -> sz : 0;
		if (lsz < k) {
			l = x;
			split(x -> r, k - lsz - 1, l -> r, r);
			pushup(l);
		}
		else {
			r = x;
			split(x -> l, k, l, r -> l);
			pushup(r);
		}
	}

	Node* merge(Node *a, Node *b) {
		if (!a || !b) return a ? a : b;
		if (a -> fix < b -> fix) {
			pushdown(a);
			a -> r = merge(a -> r, b);
			pushup(a);
			return a;
		}
		else {
			pushdown(b);
			b -> l = merge(a, b -> l);
			pushup(b);
			return b;
		}
		return NULL;
	}

	void insert(int pos, int tot) {
		Node *l, *r;
		split(root, pos, l, r);
		for (; tot --; ) {
			int x;
			scanf("%d", &x);
			l = merge(l, newnode(x));
		}
		root = merge(l, r);
	}

	void erase(int pos, int tot) {
		Node *l, *m, *r;
		split(root, pos - 1, l, r);
		split(r, tot, m, r);
		freetreap(m);
		root = merge(l, r);
	}

	void make_same(int pos, int tot) {
		int x;
		scanf("%d", &x);
		Node *l, *m, *r;
		split(root, pos - 1, l, r);
		split(r, tot, m, r);
		m -> val = x;
		m -> lazy = x;
		m -> sum = 1LL * x * m -> sz;
		m -> maxprv = m -> maxsuf = max(0LL, m -> sum);
		m -> maxsum = max(m -> sum, 1LL * x);
		root = merge(merge(l, m), r);
	}

	void reverse(int pos, int tot) {
		Node *l, *m, *r;
		split(root, pos - 1, l, r);
		split(r, tot, m, r);
		m -> rev ^= 1;
		if (m -> rev) {
			swap(m -> l, m -> r);
			swap(m -> maxprv, m -> maxsuf);
		}
		root = merge(merge(l, m), r);
	}

	void get_sum(int pos, int tot) {
		Node *l, *m, *r;
		split(root, pos - 1, l, r);
		split(r, tot, m, r);
		if (m) printf("%lld\n", m -> sum);
		else printf("0\n");
		root = merge(merge(l, m), r);
	}

	void max_sum() {
		printf("%lld\n", root -> maxsum);
	}

	void dbg(Node *x) {
		if (!x) return;
		pushdown(x);
		dbg(x -> l);
		printf("%lld ", x -> val);
		dbg(x -> r);
	}
}

int main() {
	Treap :: init();
	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++ i) {
		int x;
		scanf("%d", &x);
		Treap :: root = Treap :: merge(Treap :: root, Treap :: newnode(x));
	}
	for (; q --; ) {
		char tp[15];
		scanf("%s", tp);
		if (!strcmp(tp, "MAX-SUM")) Treap :: max_sum();
		else {
			int pos, tot;
			scanf("%d%d", &pos, &tot);
			if (!strcmp(tp, "INSERT")) Treap :: insert(pos, tot);
			if (!strcmp(tp, "DELETE")) Treap :: erase(pos, tot);
			if (!strcmp(tp, "MAKE-SAME")) Treap :: make_same(pos, tot);
			if (!strcmp(tp, "REVERSE")) Treap :: reverse(pos, tot);
			if (!strcmp(tp, "GET-SUM")) Treap :: get_sum(pos, tot);
		}
//		Treap :: dbg(Treap :: root); puts("");
	}
	return 0;
}
