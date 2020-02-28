/*
	Notes: Be careful with compression path when you can't use it (example: for undo)
	
	Complexity: O(a(n)) with compression path
				O(log n) without compression path
*/
struct union_find
{
	vector<int> p;

	union_find(int n) : p(n, -1) {}

	bool join(int u, int v)
	{
		if ((u = root(u)) == (v = root(v)))
			return false;
		if (p[u] > p[v])
			swap(u, v);
		p[u] += p[v];
		p[v] = u;
		return true;
	}

	int root(int u) { return p[u] < 0 ? u : p[u] = root(p[u]); }
	int size(int u) { return -p[root(u)]; }
};
