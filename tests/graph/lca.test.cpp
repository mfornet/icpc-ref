#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/lca.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	lowest_common_ancestor<int> lca(n);
	for (int v = 1, u; v < n; ++v)
	{
		cin >> u;
		lca.add_edge(u, v, 1);
	}
	lca.build();
	for (int u, v; q--; )
	{
		cin >> u >> v;
		cout << lca.query(u, v).F << "\n";
	}

	return 0;
}
