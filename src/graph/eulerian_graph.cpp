typedef vector<vector<int>> vvi;

/*
	Euler path undirected (path to use once all edges)
	the degree of all nodes must be even (euler cycle)
	or only exists two odd nodes (euler path)
*/
void visit(const vvi &G, vvi &adj, int s, vector<int> &path)
{
	for (auto v : G[s])
		if (adj[s][v])
		{
			--adj[s][v], --adj[v][s];
			visit(G, adj, v, path);
		}
	path.push_back(s);
}

bool euler_path(const vvi &G, int s, vector<int> &path)
{
	int n = G.size(), odd = 0, m = 0;
	for (int i = 0; i < n; ++i)
	{
		odd += G[i].size() & 1;
		m += G[i].size();
	}

	if (odd == 0 || (odd == 2 && G[s].size() % 2 == 0))
	{
		vvi adj(n, vector<int>(n));
		for (int u = 0; u < n; ++u)
			for (auto v : G[u])
				++adj[u][v];

		visit(G, adj, s, path);
		reverse(path.begin(), path.end());
		return path.size() == m / 2 + 1;
	}
	return false;
}

/*
	Euler path directed (path to use once all edges)
	the in-degree - out-degree == 0 for all nodes (euler cycle)
	or only exists two nodes with |in-degree - out-degree| == 1 (euler path)
*/
void visit(vvi &G, int u, vector<int>& path)
{
	while (!G[u].empty())
	{
		int v = G[u].back();
		G[u].pop_back();
		visit(G, v, path);
	}
	path.push_back(u);
}

bool euler_path(vvi G, int s, vector<int> &path)
{
	int n = G.size(), m = 0;
	vector<int> deg(n);
	for (int u = 0; u < n; ++u)
	{
		m += G[u].size();
		for (auto v : G[u])
			--deg[v];			//  in-deg
		deg[u] += G[u].size();	// out-deg
	}

	int k = n - count(deg.begin(), deg.end(), 0);
	if (k == 0 || (k == 2 && deg[s] == 1))
	{
		visit(G, s, path);
		reverse(path.begin(), path.end());
		return path.size() == m + 1;
	}
	return false;
}
