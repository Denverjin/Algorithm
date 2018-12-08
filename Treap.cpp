#include <cstdio>
#include <cstdlib>
#include <queue>

const int N = 111111;

namespace Treap {
	struct Node {
		int val, fix, sz;
		Node *l, *r;
	} node[N];
	Node* root;
	std :: queue <Node*> freenodes;

	void init() {
		for (int i = 0; i < N; ++ i) freenodes.push(&node[i]);
		root = NULL;
	}

	Node* newnode(int val) {
		Node *x = freenodes.front();
		freenodes.pop();
		x -> val = val;
		x -> sz = 1;
		x -> fix = rand();
		x -> l = x -> r = NULL;
		return x;
	}

	void freenode(Node *x) {
		freenodes.push(x);
	}

	void pushup(Node *x) {
		x -> sz = 1;
		if (x -> l) x -> sz += x -> l -> sz;
		if (x -> r) x -> sz += x -> r -> sz;
	}

	void split(Node *x, int v, Node *&a, Node *&b) {
		if (!x) {
			a = b = NULL;
			return;
		}
		if (x -> val <= v) {
			a = x;
			split(x -> r, v, a -> r, b);
			pushup(a);
		}
		else {
			b = x;
			split(x -> l, v, a, b -> l);
			pushup(b);
		}
	}

	Node* merge(Node *a, Node *b) {
		if (!a || !b) return a ? a : b;
		if (a -> fix < b -> fix) {
			a -> r = merge(a -> r, b);
			pushup(a);
			return a;
		}
		else {
			b -> l = merge(a, b -> l);
			pushup(b);
			return b;
		}
		return NULL;
	}

	void insert(int v) {
		Node *l, *r;
		split(root, v, l, r);
		root = merge(merge(l, newnode(v)), r);
	}

	void erase(int v) {
		Node *l, *m, *r;
		split(root, v, l, r);
		split(l, v - 1, l, m);
		freenode(m);
		m = merge(m -> l, m -> r);
		root = merge(merge(l, m), r);
	}

	int rnk(int v) {
		Node *l, *r;
		split(root, v - 1, l, r);
		int ans = (l ? l -> sz : 0) + 1;
		root = merge(l, r);
		return ans;
	}

	int kth(int k, Node *x = root) {
		int lsz = (x -> l ? x -> l -> sz : 0);
		if (lsz + 1 < k) return kth(k - lsz - 1, x -> r);
		else if (lsz + 1 == k) return x -> val;
		return kth(k, x -> l);
	}

	int lower_bound(int v) {
		Node *l, *r;
		split(root, v - 1, l, r);
		int ans = kth(l -> sz, l);
		root = merge(l, r);
		return ans;
	}

	int upper_bound(int v) {
		Node *l, *r;
		split(root, v, l, r);
		int ans = kth(1, r);
		root = merge(l, r);
		return ans;
	}
}

int main() {
	Treap :: init();
	int q;
	scanf("%d", &q);
	while (q --) {
		int tp, x;
		scanf("%d%d", &tp, &x);
		if (tp == 1) Treap :: insert(x);
		else if (tp == 2) Treap :: erase(x);
		else if (tp == 3) printf("%d\n", Treap :: rnk(x));
		else if (tp == 4) printf("%d\n", Treap :: kth(x));
		else if (tp == 5) printf("%d\n", Treap :: lower_bound(x));
		else printf("%d\n", Treap :: upper_bound(x));
	}
	return 0;
}
