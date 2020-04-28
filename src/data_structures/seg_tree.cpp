template<class node>
struct segment_tree
{
	using node_container = decltype(node().nod);
	using lazy_container = decltype(node().lazy);

private:
	inline void push(int x, int b, int e, int m)
	{
		if (st[x].lazy())
		{
			st[x + 1].apply(b, m, st[x].lazy, 0);
			st[x + ((m - b) << 1)].apply(m, e, st[x].lazy, m-b);
			st[x].lazy = lazy_container();
		}
	}

	template<typename RAIter>
	void build(int x, int b, int e, const RAIter &a)
	{
		if (b+1 == e)
		{
			st[x].nod.build(a[b]);
			return;
		}

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);

		build(x + 1, b, m, a);
		build(y, m, e, a);
		st[x].nod = st[x + 1].nod + st[y].nod;
	}

	void update_(int x, int b, int e)
	{
		if (lo <= b && e <= hi)
		{
			st[x].apply(b, e, lazy, b-lo);
			return;
		}

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);
		push(x, b, e, m);

		if (lo < m) update_(x + 1, b, m);
		if (m < hi) update_(y, m, e);
		st[x].nod = st[x + 1].nod + st[y].nod;
	}

	node_container query(int x, int b, int e)
	{
		if (lo <= b && e <= hi)
			return st[x].nod;

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);
		push(x, b, e, m);

		if (m >= hi) return query(x + 1, b, m);
		if (m <= lo) return query(y, m, e);
		return query(x + 1, b, m) + query(y, m, e);
	}

	template<class P>
	int find_first(int x, int b, int e, const P &f)
	{
		if (b+1 == e)
			return f(st[x]) ? b : -1;

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);
		push(x, b, e, m);

		if (lo < m && f(st[x + 1]))
		{
			auto t = find_first(x + 1, b, m, f);
			if (t != -1) return t;
		}
		if (m < hi && f(st[y]))
			return find_first(y, m, e, f);
		return -1;
	}

	template<class P>
	int find_last(int x, int b, int e, const P &f)
	{
		if (b+1 == e)
			return f(st[x]) ? b : -1;

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);
		push(x, b, e, m);

		if (m < hi && f(st[y]))
		{
			auto t = find_last(y, m, e, f);
			if (t != -1) return t;
		}
		if (lo < m && f(st[x + 1]))
			return find_last(x + 1, b, m, f);
		return -1;
	}

	lazy_container lazy;
	int n, lo, hi;
	vector<node> st;

public:
	template<typename RAIter>
	void build(const RAIter &a)
	{
		build(0, 0, n, a);
	}

	void update(int l, int r, const lazy_container &x)
	{
		lo = l, hi = r, lazy = x, update_(0, 0, n);
	}

	node_container query(int l, int r)
	{
		return lo = l, hi = r, query(0, 0, n);
	}

	template<class P>
	int find_first(int l, int r, const P &f)
	{
		return lo = l, hi = r, find_first(0, 0, n, f);
	}

	template<class P>
	int find_last(int l, int r, const P &f)
	{
		return lo = l, hi = r, find_last(0, 0, n, f);
	}

	segment_tree(int n) : n(n), st(2 * n - 1) {}
};

struct node // arithmetic progression
{
	struct node_container
	{
		ll x;

		template<typename T>
		inline void build(const T &a) // build(leave) from a
		{

		}

		friend node_container operator+(node_container l, const node_container &r) // merge l and r
		{
			l.x += r.x;
			return l;
		}

		node_container() : x(0) {}
	} nod;

	struct lazy_container
	{
		bool clear;
		ll first, dif;

		inline bool operator()() // has lazy
		{
			return first != 0 || dif != 0 || clear;
		}

		lazy_container(bool clear = 0, ll first = 0, ll dif = 0) : clear(clear), first(first), dif(dif) {}
	} lazy;

	inline void apply(int l, int r, const lazy_container &p, int szl) // apply lazy
	{
		if (p.clear)
		{
			nod.x = 0;
			lazy = lazy_container();
			lazy.clear = 1;
		}
		int sz = r-l;
		ll first = p.first + szl * p.dif;
		nod.x += first * sz + ((ll)sz-1) * sz / 2 * p.dif;
		lazy.first += first;
		lazy.dif += p.dif;
	}
};