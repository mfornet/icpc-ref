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

#include "../../src/data_structures/union_find.cpp"
#include "../../src/graph/lca_offline.cpp"

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
	vector<pair<int, int>> que(q);
	for (auto &i : que)
		cin >> i.F >> i.S;

	for (auto i : lca_offline(adj, que, 0))
		cout << i << "\n";

	return 0;
}
