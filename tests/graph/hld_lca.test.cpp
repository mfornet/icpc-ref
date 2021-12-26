#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/heavy_light_decomposition.cpp"

struct dummy
{
	dummy(int n) {}
	int query(int a, int b);
	void update(int a, int b, int c);
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	heavy_light_decomposition<dummy> lca(n);
	for (int v = 1, u; v < n; ++v)
	{
		cin >> u;
		lca.add_edge(u, v);
	}
	lca.rootify();
	for (int u, v; q--; )
	{
		cin >> u >> v;
		cout << lca.lca(u, v) << "\n";
	}

	return 0;
}
