const int mod = 998244353;
const int root = 5; // primitive root of mod

int pow_mod(int a, int n)
{
	int r = 1;
	for (; n; n >>= 1)
	{
		if (n&1)
			r = (ll)r*a % mod;
		a = (ll)a*a % mod;
	}
	return r;
}

void ntt(int a[], int n, int sign)
{
	for (int i = 1, j = 0; i < n - 1; ++i)
	{
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
		if (i < j) swap(a[i], a[j]);
	}

	for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
	{
		int wm = pow_mod(root, (mod - 1) / m);
		if (sign < 0) wm = pow_mod(wm, mod - 2);

		for (int i = 0, w = 1; i < n; i += m, w = 1)
			for (int j = i; j < i + mh; ++j)
			{
				int x = a[j], y = (ll) a[j + mh] * w % mod;
				a[j] = x + y; a[j + mh] = x - y;
				if (a[j] >= mod) a[j] -= mod;
				if (a[j + mh] < 0) a[j + mh] += mod;
				w = (ll) w * wm % mod;
			}
	}

	if (sign < 0)
	{
		int inv = pow_mod(n, mod - 2);
		for (int i = 0; i < n; ++i) a[i] = (ll) a[i] * inv % mod;
	}
}
/*
// sz should by a power of two
ntt(p, sz, +1);
for (int i = 0; i < sz; ++i) p[i] = pow_mod(p[i], n);
ntt(p, sz, -1);
*/
