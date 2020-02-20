
/*
**	Description: Find a function f, wich map the vertex of a tree
**	into non negative integers. And satisfy that if u and v are distincts
**	vertices and f(u) = f(v), then on the simple path that from u
**	to v there is a vertex w such that f(w) > f(u).
**	The algorithm find a function f such that max f(u) is minimum
**	among all function with the path property.
**	For convenience is returned a vector with the values of 2^f(u)
**	Complexity: O(n)
*/

vector<int> strategy_function(const vector<vector<int>> &g)
{
	vector<int> label(g.size());
	function<int(int)> dfs = [&](int u)
	{
		label[u] = -1;
		int used = 0, more = 0;
		for (int v : g[u])
			if (!label[v])
			{
				int mask = dfs(v);
				more |= mask & used;
				used |= mask;
			}
		for (int k : {1, 2, 4, 8, 16})
			more |= more >> k;
		++more;
		int possible = ~used & -more;
		label[u] = possible & -possible;
		used |= label[u];
		used &= -label[u];
		return used;
	};
	dfs(0);
	return label;
}
