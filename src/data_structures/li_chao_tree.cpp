struct li_chao_tree
{
	struct side
	{
		point p;
		side() : p(1e6+5, 1e18+5) {}
		side(point x) : p(x) {}
	};

	inline static ll f(side s, ll x)
	{
		return dot(s.p, { x*x, 1LL });
	}

	vector<side> st;
	li_chao_tree(int n) : st(2 * n - 1) {}

	void update(int x, int b, int e, side s)
	{
		int m = (b+e)>>1;

		bool l = f(st[x], b) > f(s, b);
		bool r = f(st[x], m) > f(s, m);

		if (r) swap(st[x], s);

		if (b + 1 == e) return;
		if (l != r) update(x + 1, b, m, s);
		else update(x + ((m - b) << 1), m, e, s);
	}

	ll query(int x, int b, int e, ll p)
	{
		ll r = f(st[x], p);
		if (b + 1 == e) return r;
		int m = (b+e)>>1;
		if (p < m)
			return min(r, query(x + 1, b, m, p));
		return min(r, query(x + ((m - b) << 1), m, e, p));
	}
};