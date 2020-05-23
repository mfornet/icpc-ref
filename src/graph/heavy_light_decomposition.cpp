/*
	Notes: pos is 0-indexed, operations are over nodes by default
	       ** change the return of query and query_up **
	       ** on query_up make sure 'ans' contains a neutral value for the desired operation(sum by default) **
	       ** for operations over the edges change excl_l to true **
	       ** for updates on subtrees use rootify_rec, nodes in subtree of u are in [pos_u, endpos_u) **

	Complexity: O(n) rootify, O(log n) lca, O(log n * data_structure_cost_of) update and query
*/

template<class data_structure, bool excl_l = false>
struct heavy_light_decomposition
{
	int n;
	vector<vector<int>> G;
	vector<int> parent, depth, head, pos, endpos;
	data_structure ds;
	heavy_light_decomposition(int n) :n(n), G(n), parent(n, -1), depth(n), head(n), pos(n), ds(n) {}

	void add_edge(int u, int v)
	{
		G[u].push_back(v);
		G[v].push_back(u);
	}

	void rootify_rec(int r = 0)
	{
		vector<int> sz(n, 1);
		function<void(int)> dfs = [&](int u)
		{
			for (auto &v : G[u])
				if (v != parent[u])
				{
					depth[v] = depth[u] + 1;
					parent[v] = u;
					dfs(v);
					sz[u] += sz[v];
					if (sz[v] > sz[G[u][0]] || G[u][0] == parent[u])
						swap(v, G[u][0]);
				}
		};
		dfs(r);

		int p = 0;
		endpos.resize(n);
		function<void(int)> dfs_hld = [&](int u)
		{
			pos[u] = p++;
			for (auto v : G[u])
				if (v != parent[u])
				{
					head[v] = (v == G[u][0]) ? head[u] : v;
					dfs_hld(v);
				}
			endpos[u] = p;
		};
		head[r] = r;
		dfs_hld(r);
	}

	void rootify(int r = 0)
	{
		vector<int> heavy(n, -1), q(1, r), size(n, 1);

		for (int i = 0, u; i < n; ++i)
		{
			u = q[i];
			for (auto v : G[u])
				if (parent[u] != v)
					q.push_back(v), parent[v] = u, depth[v] = depth[u] + 1;
		}

		for (int i = n - 1, u; i >= 0; --i)
		{
			u = q[i];
			for (auto v : G[u])
				if (parent[u] != v)
				{
					size[u] += size[v];
					if (heavy[u] == -1 || size[v] > size[heavy[u]])
						heavy[u] = v;
				}
		}

		for (int u = 0, p = 0; u < n; ++u)
			if (u == r || heavy[parent[u]] != u)
				for (int v = u; v != -1; v = heavy[v])
					head[v] = u, pos[v] = p++;
	}

	int lca(int u, int v)
	{
		while (head[u] != head[v])
		{
			if (depth[head[u]] < depth[head[v]])
				swap(u, v);
			u = parent[head[u]];
		}
		return (depth[u] < depth[v] ? u : v);
	}

	ll query_up(int u, int v, bool excl_v)
	{
		ll ans = 0;
		while (head[u] != head[v])
		{
			ans += ds.query(pos[head[u]], pos[u]+1).x;
			u = parent[head[u]];
		}
		if (pos[v]+excl_v <= pos[u]) ans += ds.query(pos[v]+excl_v, pos[u]+1).x;
		return ans;
	}

	template<typename T>
	void update_up(int u, int v, const T &c, bool excl_v)
	{
		while (head[u] != head[v])
		{
			ds.update(pos[head[u]], pos[u]+1, c);
			u = parent[head[u]];
		}
		if (pos[v]+excl_v <= pos[u]) ds.update(pos[v]+excl_v, pos[u]+1, c);
	}

	ll query(int u, int v)
	{
		int l = lca(u, v);
		return query_up(u, l, excl_l) + query_up(v, l, true);
	}

	template<typename T>
	void update(int u, int v, const T &c)
	{
		int l = lca(u, v);
		update_up(u, l, c, excl_l), update_up(v, l, c, true);
	}
};