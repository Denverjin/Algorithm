#include <cstdio>
#define ll long long

const int SZ = 1 << 16;
char buff[SZ], *pos = buff + SZ - 1;
#define getchar() ++ pos == buff + SZ ? fread(pos = buff, 1, SZ, stdin), *pos : *pos

inline ll read() {
	ll x = 0; int f = 1, c = getchar();
	for (;!isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x<<3) + (x<<1) + (c^48);
	return x * f;
}

int main() {
	return 0;
}
