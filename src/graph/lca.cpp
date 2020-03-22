/*
	Compute the lca of two nodes and the weight of the maximum edge in the path between them
	
	Notes: If the path contains 0 edges the weight of the maximum edge is set to 0
	
	Complexity: O(n log n) build, O(log n) query
*/

template<typename T, typename R = T>
struct lowest_common_ancestor
{
	vector<vector<pair<int, T>>> adj;
	vector<vector<int>> lca;
	vector<vector<R>> dist;
	vector<int> lvl;

	lowest_common_ancestor(int n) : adj(n), lca(__lg(n)+1, vector<int>(n)), dist(__lg(n)+1, vector<R>(n)), lvl(n) {}

	void add_edge(int u, int v, T w)
	{
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	void build(int r = 0)
	{
		queue<int> q;
		q.push(r);
		lca[0][r] = -1;
		lvl[r] = 0;

		for (int u, v; !q.empty(); )
		{
			u = q.front(); q.pop();
			for (auto &x : adj[u])
			{
				if ((v = x.F) == lca[0][u]) continue;

				q.push(v);
				lca[0][v] = u;
				dist[0][v] = x.S;
				lvl[v] = lvl[u] + 1;

				for (int i = 1, lg = __lg(lvl[v]); i <= lg; ++i)
				{
					lca[i][v] = lca[i - 1][lca[i - 1][v]];
					dist[i][v] = max(dist[i - 1][lca[i - 1][v]], dist[i - 1][v]);
				}
			}
		}
	}

	pair<int, R> query(int u, int v)
	{
		if (lvl[v] > lvl[u])
			swap(u, v);

		R D = 0;
		if (lvl[u])
			for (int i = __lg(lvl[u]); i >= 0; --i)
				if (lvl[u] - (1 << i) >= lvl[v])
				{
					D = max(D, dist[i][u]);
					u = lca[i][u];
				}

		if (u == v)
			return { u, D };

		if (lvl[u])
			for (int i = __lg(lvl[u]); i >= 0; --i)
				if ((1 << i) <= lvl[u] && lca[i][u] != lca[i][v])
				{
					D = max({D, dist[i][v], dist[i][u]});
					u = lca[i][u];
					v = lca[i][v];
				}

		D = max({D, dist[0][u], dist[0][v]});
		return { lca[0][u], D };
	}
};
