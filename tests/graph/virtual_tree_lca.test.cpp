#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>

using namespace std;

#ifdef NeverBeRed
#include "debug.h"
#else
#define debug(...) 9715
#endif
typedef long long ll;
typedef long double ld;
typedef complex<ld> point;
#define F first
#define S second

#include "../../src/graph/virtual_tree.cpp"

int main()
{
	#ifdef TurnRed
		//freopen("a.in", "r", stdin);
		//freopen("a.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for (int v = 1, u; v < n; ++v)
	{
		cin >> u;
		adj[u].push_back(v);
	}
	virtual_tree vt(adj);
	for (int u, v; q--; )
	{
		cin >> u >> v;
		cout << vt.lca(u, v) << "\n";
	}

	return 0;
}
