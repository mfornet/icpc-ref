namespace or_transform
{
	void transform(ll a[], int n, int inv = +1)
	{
		if (n <= 1) return;
		transform(a, n / 2, inv);
		transform(a + n / 2, n / 2, inv);
		for (int i = 0; i < n / 2; ++i)
		{
			ll u = a[i], v = a[i + n / 2];
			a[i] = u;
			a[i + n / 2] = v + inv * u;
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

		transform(a.data(), n, -1);

		return a;
	}
} 
