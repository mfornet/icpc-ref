vector<int> lca_offline(vector<vector<int>> &adj, vector<pair<int, int>> &queries, int root = 0)
{
	int n = adj.size();
	vector<int> ancestor(n, -1), ans(queries.size());
	vector<vector<int>> q(n);
	union_find uf(n);
	for (auto &i : queries)
		q[i.F].push_back(&i-&queries[0]),
		q[i.S].push_back(&i-&queries[0]);

	function<void(int)> dfs = [&](int u)
	{
		ancestor[u] = u;
		for (auto v : adj[u])
			if (ancestor[v] == -1)
			{
				dfs(v);
				uf.join(u, v);
				ancestor[uf.root(u)] = u;
			}
		for (auto i : q[u])
		{
			int v = u ^ queries[i].F ^ queries[i].S;
			if (ancestor[v] != -1)
				ans[i] = ancestor[uf.root(v)];
		}
	};
	dfs(root);
	return ans;
}
