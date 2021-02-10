/*
	Notes: Be careful with path compression when you can't use it (example: for undo)
	
	Complexity: O(a(n)) with path compression, O(log n) without path compression
*/
struct union_find
{
	vector<int> p;
	// vector<pair<int, int>> stk;

	union_find(int n = 0) : p(n, -1) {}

	bool join(int u, int v)
	{
		// stk.push_back({ -1, -1 });
		if ((u = root(u)) == (v = root(v)))
			return false;
		if (p[u] > p[v])
			swap(u, v);
		// stk.back() = { v, p[v] };
		p[u] += p[v];
		p[v] = u;
		return true;
	}

	// void undo() // remove path compression
	// {
	// 	int v, pv; tie(v, pv) = stk.back();
	// 	stk.pop_back();
	// 	if (v != -1) p[p[v]] -= pv, p[v] = pv;
	// }

	int root(int u) { return p[u] < 0 ? u : p[u] = root(p[u]); }
	int size(int u) { return -p[root(u)]; }
};