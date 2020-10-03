#define PROBLEM "https://judge.yosupo.jp/problem/scc"

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

#include "../../src/graph/strongly_connected_component.cpp"

int main()
{
	#ifdef TurnRed
		//freopen("a.in", "r", stdin);
		//freopen("a.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adj(n);
	for (int i = 0, u, v; i < m; ++i)
	{
		cin >> u >> v;
		adj[u].push_back(v);
	}

	auto scc = strongly_connected_components_it(adj);
	cout << scc.size() << "\n";
	reverse(scc.begin(), scc.end());
	for (auto &i : scc)
	{
		cout << i.size();
		for (auto j : i) cout << " " << j;
		cout << "\n";
	}

	return 0;
}
