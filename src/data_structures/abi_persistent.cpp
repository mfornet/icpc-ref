template<typename T>
struct fenwick
{
	int n;
	vector<vector<pair<int, T>>> f;
	fenwick(int n) : n(n), f(n+1, vector<pair<int, T>>(1, { -1, 0 })) {}

	T query(int p, int pos)
	{
		T ret = 0;
		for (++p; p > 0; p -= p & -p)
			ret += prev(upper_bound(f[p].begin(), f[p].end(), pos,
			    [](int x, const pair<int, T> &t){ return x < t.F; }))->S;
		return ret;
	}

	void update(int p, T x, int q)
	{
		for (++p; p <= n; p += p & -p)
		{
			if (f[p].back().F < q) f[p].push_back({ q, f[p].back().S });
			f[p].back().S += x;
		}
	}
};