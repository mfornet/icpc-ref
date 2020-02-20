vector<vector<pii>> biconnected_components(vector<vector<pii>> &adj)
{
	int n = adj.size(), t;
	int m = 0; for (auto &l : adj) for (auto v : l) m = max(m, v.S);
	vector<pii> stk;
	vector<bool> mark(m+1);
	vector<vector<pii>> comps;
	vector<int> low(n), num(n);

	function<void(int)> dfs = [&](int u)
	{
		num[u] = low[u] = ++t;

		int v, e;
		for (auto i : adj[u])
		{
			tie(v, e) = i;

			if (!mark[e])
				stk.push_back(pii(u, v)), mark[e] = true;

			if (!num[v])
			{
				dfs(v);
				if (low[v] >= num[u])
				{
					comps.push_back({});
					do
					{
						comps.back().push_back(stk.back()), stk.pop_back();
					} while (comps.back().back() != pii(u, v));
				}
				else low[u] = min(low[u], low[v]);
			}
			else low[u] = min(low[u], num[v]);
		}
	};
	for (int i = 0; i < n; ++i)
		if (!num[i]) t = 0, dfs(i);
	return comps;
}