#include <cstdio>

#define isdigit(c) (48 <= (c) && (c) <= 57)
template <typename T> void read(T &x) {
	x = 0; int f = 1, c = getchar();
	for (;!isdigit(c);c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c);c = getchar()) x = (x<<3) + (x<<1) + (c^48);
	x *= f;
}

int main() {
	return 0;
}
