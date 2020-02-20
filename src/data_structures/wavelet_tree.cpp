template<typename T>
struct wavelet_tree
{
	struct node
	{
		T lo, hi;
		vector<int> a;
		node *l, *r;
		node(T x, T y, int sz) :
				lo(x), hi(y), a(1, 0), l(NULL), r(NULL) { a.reserve(sz); }
	}*root;

	wavelet_tree(vector<T> &a, T MAX) // 1-based
	{
		root = build(a, 1, a.size(), 0, MAX);
	}

	node* build(vector<T> &a, int l, int r, T lo, T hi)
	{
		node *cur = new node(lo, hi, r - l + 1);
		if (lo == hi || l >= r) return cur;

		T md = (lo + hi) / 2;
		for (int i = l; i < r; ++i)
			cur->a.push_back(cur->a.back() + (a[i] <= md));

		auto p = stable_partition(a.begin() + l, a.begin() + r, [md](int lo){ return lo <= md; });
		cur->l = build(a, l, p - a.begin(), lo, md);
		cur->r = build(a, p - a.begin(), r, md + 1, hi);
		return cur;
	}

	T kth(node *cur, int l, int r, int k)
	{
		if (l > r) return 0;
		if (cur->lo == cur->hi) return cur->lo;
		int al = cur->a[l - 1], ar = cur->a[r];
		if (k <= ar - al) return kth(cur->l, al + 1, ar, k);
		return kth(cur->r, l - al, r - ar, k - ar + al);
	}

	int less_equal(node *cur, int l, int r, T k)
	{
		if (l > r || k < cur->lo) return 0;
		if (cur->hi <= k) return r - l + 1;
		int al = cur->a[l - 1], ar = cur->a[r];
		return less_equal(cur->l, al + 1, ar, k) + less_equal(cur->r, l - al, r - ar, k);
	}

	int equal(node *cur, int l, int r, T k)
	{
		if (l > r || k < cur->lo || k > cur->hi) return 0;
		if (cur->lo == cur->hi) return r - l + 1;
		int al = cur->a[l - 1], ar = cur->a[r], md = (cur->lo + cur->hi) / 2;
		if (k <= md) return equal(cur->l, al + 1, ar, k);
		return equal(cur->r, l - al, r - ar, k);
	}
};