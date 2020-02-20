struct centroid_decomposition
{
	int n;
	vector<bool> del;
	vector<vector<int>> adj;
	vector<int> size, parent;
	vector<vector<pair<int, int>>> anc;

	centroid_decomposition(int n) : n(n), del(n), adj(n), size(n), parent(n), anc(n) {};

	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int centroid(int u)
	{
		vector<int> seen = {u};
		parent[u] = -1;

		for (size_t i = 0; i < seen.size(); ++i)
		{
			u = seen[i];
			for (int v : adj[u])
				if (!del[v] && v != parent[u])
					parent[v] = u, seen.push_back(v);
		}

		for (int sz = seen.size(), i = sz - 1, mx = 0; i >= 0; --i, mx = 0)
		{
			size[u = seen[i]] = 1;
			for (int v : adj[u])
				if (!del[v] && v != parent[u])
					size[u] += size[v], mx = max(mx, size[v]);
			if (max(sz - size[u], mx) <= sz / 2)
				return u;
		}

		return -1;
	}

	void dfs(int u, int p, int d, int c)
	{
		anc[u].push_back({c, d});
		for (int v : adj[u])
			if (!del[v] && v != p)
				dfs(v, u, d + 1, c);
	}

	void rootify(int r)
	{
		int c = centroid(r);
		assert(c != -1);
		del[c] = true;
		dfs(c, -1, 0, c);

		for (int v : adj[c])
			if (!del[v]) rootify(v);
	}

	void update(int u)
	{
		for(auto p : anc[u]) ;
	}

	void query(int u)
	{
		for(auto p : anc[u]) ;
	}
};