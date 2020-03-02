/*
	Compute the lca of two nodes and the distance between them
	Compress a subset of k nodes into a tree with the same structure
	
	Notes: (ft, pos) are only necessary for compress
	       after compress every node u is mapped to pos[u]

	Complexity: O(n log n) build, O(1) lca, O(k log k) compress

	Tested: https://codeforces.com/contest/1320/submission/72221211
*/
struct virtual_tree
{
	vector<int> tour, depth, dt, ft, pos;
	vector<vector<int>> table;

	virtual_tree(vector<vector<int>> &adj)
	{
		dt = ft = pos = vector<int>(adj.size());
		function<void(int, int, int)> dfs = [&](int u, int p, int d)
		{
			dt[u] = tour.size();
			tour.push_back(u);
			depth.push_back(d);

			for (int v : adj[u])
				if (v != p)
				{
					dfs(v, u, d+1);
					tour.push_back(u);
					depth.push_back(d);
				}

			ft[u] = tour.size();
		};
		dfs(0, -1, 0);

		int t = tour.size(), lg = __lg(t);
		table.resize(lg+1, vector<int>(t));
		iota(table[0].begin(), table[0].end(), 0);
		for (int j = 0; j < lg; ++j)
			for (int i = 0; i + (1<<(j+1)) <= t; ++i)
				table[j+1][i] = argmin(table[j][i], table[j][i+(1<<j)]);
	}

	inline int argmin(int i, int j) { return depth[i] < depth[j] ? i : j; }

	inline int lca(int u, int v)
	{
		int i = dt[u], j = dt[v];
		if (i > j) swap(i, j);
		int l = __lg(j - i);
		return i == j ? u : tour[argmin(table[l][i], table[l][j-(1<<l)])];
	}

	inline int dist(int u, int v)
	{
		return depth[dt[u]] + depth[dt[v]] - 2*depth[dt[lca(u, v)]];
	}

	vector<vector<pair<int, int>>> compress(vector<int> &a)
	{
		auto cmp = [&](const int &x, const int &y) { return dt[x] < dt[y]; };

		auto c = a;
		sort(c.begin(), c.end(), cmp);
		for (int i = 1, sz = c.size(); i < sz; ++i)
			c.push_back(lca(c[i-1], c[i]));

		sort(c.begin(), c.end(), cmp);
		c.erase(unique(c.begin(), c.end()), c.end());

		vector<vector<pair<int, int>>> g(c.size());
		vector<int> s;

		// u become pos[u]
		for (auto &u : c)
		{
			pos[u] = &u-&c[0];
			while (!s.empty() && !(dt[s.back()] <= dt[u] && dt[u] <= ft[s.back()]))
				s.pop_back();

			if (!s.empty())
			{
				int d = dist(s.back(), u);
				g[pos[s.back()]].push_back({ pos[u], d });
				g[pos[u]].push_back({ pos[s.back()], d });
			}

			s.push_back(u);
		}

		return g;
	}
};