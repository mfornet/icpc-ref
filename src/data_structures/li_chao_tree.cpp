/*
	Update: add functions like a*x + b
	Query: return the minimim evaluation for a fixed x

	Notes: call query and update with 0, 0, n, ...
	       *for large x -> compress coordinates

	Complexity: O(log n) query and update
*/
template<class T>
struct li_chao_tree
{
	vector<T> st;
	li_chao_tree(int n) : st(2 * n - 1) {}

	void update(int x, int b, int e, T s)
	{
		int m = (b+e)>>1;

		bool l = T::f(st[x], b) > T::f(s, b);
		bool r = T::f(st[x], m) > T::f(s, m);

		if (r) swap(st[x], s);

		if (b + 1 == e) return;
		if (l != r) update(x + 1, b, m, s);
		else update(x + ((m - b) << 1), m, e, s);
	}

	ll query(int x, int b, int e, ll p)
	{
		ll r = T::f(st[x], p);
		if (b + 1 == e) return r;
		int m = (b+e)>>1;
		if (p < m)
			return min(r, query(x + 1, b, m, p));
		return min(r, query(x + ((m - b) << 1), m, e, p));
	}
};

/* Example for min a*x + b
struct side
{
	point p;
	side() : p(0, 2e18+5) {}
	side(point x) : p(x) {}

	inline static ll f(side s, ll x)
	{
		return dot(s.p, { x, 1LL });
	}
};
*/