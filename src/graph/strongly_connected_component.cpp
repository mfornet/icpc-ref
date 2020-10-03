vector<vector<int>> strongly_connected_components(const vector<vector<int>> &g)
{
	int n = g.size();
	vector<vector<int>> scc;
	vector<int> S, B, I(n, -1);

	function<void(int)> dfs = [&](int u)
	{
		B.push_back(I[u] = S.size());
		S.push_back(u);

		for (int v : g[u])
		{
			if (!~I[v]) dfs(v);
			else while (I[v] < B.back()) B.pop_back();
		}

		if (I[u] == B.back())
		{
			scc.push_back({});
			B.pop_back();

			while (I[u] < (int) S.size())
			{
				scc.back().push_back(S.back());
				I[S.back()] = n + scc.size();
				S.pop_back();
			}
		}
	};

	for (int u = 0; u < n; ++u)
		if (!~I[u]) dfs(u);

	return scc;
}

vector<vector<int>> strongly_connected_components_it(const vector<vector<int>> &g)
{
	int n = g.size();
	vector<vector<int>> scc;
	vector<int> S, B, I(n, -1), ord, edge(n, -1);

	auto run = [&]()
	{
		while (!ord.empty())
		{
			int u = ord.back();
			ord.pop_back();

			if (edge[u] == -1)
			{
				B.push_back(I[u] = S.size());
				S.push_back(u);
			}

			bool done = true;

			while (++edge[u] < g[u].size())
			{
				int v = g[u][edge[u]];
				if (!~I[v])
				{
					ord.emplace_back(u);
					ord.emplace_back(v);
					done = false;
					break;
				}
				else while (I[v] < B.back()) B.pop_back();
			}

			if (done && I[u] == B.back())
			{
				scc.push_back({});
				B.pop_back();

				while (I[u] < (int) S.size())
				{
					scc.back().push_back(S.back());
					I[S.back()] = n + scc.size();
					S.pop_back();
				}
			}
		}
	};

	for (int u = 0; u < n; ++u)
		if (!~I[u])
		{
			ord.emplace_back(u);
			run();
		}

	return scc;
}
