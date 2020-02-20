/*
	Dominator Tree (Lengauer-Tarjan)

	Tested: SPOJ EN
	Complexity: O(m log n)

	in control flow graphs, a node d dominates a node n
	if every path from the entry node to n must go through d
*/

vector<int> dominators(const vector<vector<int>> &g, int r)
{
	int n = g.size();
	vector<int> ord, rank(n, n), prev(n, n), anc(n, n), idom(n, n), semi(n), low(n);
	vector<vector<int>> g_rev(n), dom(n);
	function<void(int)> dfs = [&](int u)
	{
		rank[u] = ord.size();
		ord.emplace_back(u);
		for (int v : g[u])
		{
			g_rev[v].emplace_back(u);
			if (rank[v] < n) continue;
			prev[v] = u;
			dfs(v);
		}
	};
	dfs(r);
	for (int i = 0; i < n; ++i) semi[i] = low[i] = i;
	function<int(int)> eval = [&](int v)
	{
		if (anc[v] < n && anc[anc[v]] < n)
		{
			int x = eval(anc[v]);
			if (rank[semi[low[v]]] > rank[semi[x]]) low[v] = x;
			anc[v] = anc[anc[v]];
		}
		return low[v];
	};
	for (int i = (int) ord.size() - 1; i >= 1; --i)
	{
		int w = ord[i];
		for (int v : g_rev[w])
		{
			int u = eval(v);
        	if (rank[semi[w]] > rank[semi[u]]) semi[w] = semi[u];
		}
		dom[semi[w]].emplace_back(w);
		anc[w] = prev[w];
		for (int v : dom[prev[w]])
		{
			int u = eval(v);
			idom[v] = (rank[prev[w]] > rank[semi[u]] ? u : prev[w]);
		}
		dom[prev[w]].clear();
	}
	for (int i = 1; i < ord.size(); ++i)
	{
		int w = ord[i];
		if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
	}
	for (int u = 0; u < n; ++u)
		if (idom[u] >= n) idom[u] = -1;
	return idom;
}
