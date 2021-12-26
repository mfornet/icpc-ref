enum seg_type { seg_not_lazy, seg_lazy, seg_beats };
template<class node, seg_type type>
struct segment_tree
{
	using node_container = typename node::node_container;
	using lazy_container = typename node::lazy_container;
	#define enable_if(x) template <const bool T = (x), typename enable_if<T, bool>::type = 0>
	#define enable_if_not(x) template <const bool T = (x), typename enable_if<!T, bool>::type = 0>

private:
	enable_if(type != seg_not_lazy)
	inline void push(int x, int b, int e, int m)
	{
		if (st[x].lazy())
		{
			st[x + 1].apply(b, m, st[x].lazy);
			st[x + ((m - b) << 1)].apply(m, e, st[x].lazy);
			st[x].lazy = lazy_container();
		}
	}

	enable_if_not(type != seg_not_lazy)
	inline void push(int x, int b, int e, int m) {}

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

	enable_if_not(type == seg_beats)
	void update_(int x, int b, int e)
	{
		if (lo <= b && e <= hi)
		{
			st[x].apply(b, e, lazy);
			return;
		}

		int m = (b + e) >> 1;
		int y = x + ((m - b) << 1);
		push(x, b, e, m);

		if (lo < m) update_(x + 1, b, m);
		if (m < hi) update_(y, m, e);
		st[x].nod = st[x + 1].nod + st[y].nod;
	}

	enable_if(type == seg_beats)
	void update_(int x, int b, int e)
	{
		if (st[x].break_condition(lazy)) return;

		if (lo <= b && e <= hi && st[x].tag_condition(lazy))
		{
			st[x].apply(b, e, lazy);
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

struct node_max // query max, add in range
{
	struct node_container
	{
		int x;

		template<typename T>
		inline void build(const T &a) // build(leave) from a
		{
			x = a;
		}

		friend node_container operator+(node_container l, const node_container &r) // merge l and r
		{
			l.x = max(l.x, r.x);
			return l;
		}

		node_container() : x(0) {}
	} nod;

	struct lazy_container
	{
		int add;

		inline bool operator()() // has lazy
		{
			return add != 0;
		}

		lazy_container(int a = 0) : add(a) {}
	} lazy;

	inline void apply(int l, int r, lazy_container &p) // apply lazy
	{
		nod.x += p.add;
		lazy.add += p.add;
	}
};

struct node // arithmetic progression
{
	struct node_container
	{
		ll x;

		template<typename T>
		inline void build(const T &a) // build(leave) from a
		{
			x = a;
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

	inline void apply(int l, int r, lazy_container &p) // apply lazy
	{
		if (p.clear)
		{
			nod.x = 0;
			lazy = lazy_container();
			lazy.clear = 1;
		}
		int sz = r-l;
		nod.x += p.first * sz + ((ll)sz-1) * sz / 2 * p.dif;
		lazy.first += p.first;
		lazy.dif += p.dif;
		p.first += sz * p.dif;
	}
};

// Tested: https://vjudge.net/problem/HDU-5306
struct beats // segment tree beats (update a_i = min(a_i, x), query for max or sum)
{
	const static int oo = numeric_limits<int>::max();

	struct node_container
	{
		int mx;  // max
		int mxc; // max count
		int mx2; // second strict max
		ll sum;

		template<typename T>
		inline void build(const T &a) // build(leave) from a
		{
			mx = a;
			mxc = 1;
			mx2 = -1;
			sum = a;
		}

		friend node_container operator+(node_container l, const node_container &r) // merge l and r
		{
			if (l.mx != r.mx)
			{
				if (r.mx > l.mx) l.mx2 = max(l.mx, r.mx2), l.mx = r.mx, l.mxc = r.mxc;
				else l.mx2 = max(l.mx2, r.mx);
			}
			else
			{
				l.mxc += r.mxc;
				l.mx2 = max(l.mx2, r.mx2);
			}
			l.sum += r.sum;
			return l;
		}

		node_container() : mx(0), mxc(1), mx2(-1), sum(0) {}
	} nod;

	struct lazy_container
	{
		int x;

		inline bool operator()() // has lazy
		{
			return x != oo;
		}

		lazy_container(int x = oo) : x(x) {}
	} lazy;

	inline void apply(int l, int r, lazy_container &p) // apply lazy
	{
		if (!break_condition(p))
		{
			nod.sum -= (ll)(nod.mx - p.x) * nod.mxc;
			nod.mx = p.x;
			lazy.x = p.x;
		}
	}

	inline bool tag_condition(const lazy_container &p)
	{
		return nod.mx2 < p.x;
	}

	inline bool break_condition(const lazy_container &p)
	{
		return nod.mx <= p.x;
	}
};
