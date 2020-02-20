namespace and_transform
{
	void transform(ll a[], int n, bool inv = false)
	{
		for (int len = 1; 2 * len <= n; len <<= 1)
			for (int i = 0; i < n; i += 2 * len)
				for (int j = 0; j < len; j++)
				{
					ll u = a[i + j], v = a[i + len + j];

					if (!inv)
					{
						a[i + j] = v;
						a[i + len + j] = u + v;
					}
					else
					{
						a[i + j] = -u + v;
						a[i + len + j] = u;
					}
				}
	}

	vector<ll> convolve(vector<ll> a, vector<ll> b)
	{
		int sz = max(a.size(), b.size()), n = 1;
		while (n < sz) n *= 2;
		a.resize(n);
		b.resize(n);

		transform(a.data(), n);
		transform(b.data(), n);
		for (int i = 0; i < n; ++i) a[i] *= b[i];

		transform(a.data(), n, true);

		return a;
	}
}