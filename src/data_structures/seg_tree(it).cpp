struct segment_tree
{
	int n;
	vector<ll> a;

	segment_tree(int n) : n(n), a(2 * n) {}

	void update(int p, ll v)
	{
		for (a[p += n] = v; p /= 2;)
			a[p] = __gcd(a[2 * p], a[2 * p + 1]);
	}

	ll query(int l, int r)
	{
		ll g = 0;

		for (l += n, r += n; l < r; l /= 2, r /= 2)
		{
			if (l & 1) g = __gcd(g, a[l++]);
			if (r & 1) g = __gcd(g, a[--r]);
		}

		return g;
	}
};