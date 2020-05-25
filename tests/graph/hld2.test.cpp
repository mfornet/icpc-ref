#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/heavy_light_decomposition.cpp"
#include "../../src/data_structures/seg_tree.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	heavy_light_decomposition<segment_tree<node, seg_lazy>> hld(n);
	vector<int> a(n);
	for (auto &i : a) cin >> i;
	for (int i = 1, u, v; i < n; ++i)
	{
		cin >> u >> v;
		hld.add_edge(u, v);
	}
	
	hld.rootify();
	for (int i = 0; i < n; ++i)
		hld.update(i, i, node::lazy_container(0, a[i], 0));
	
	for (int t, u, x; q--; )
	{
		cin >> t >> u >> x;
		if (t == 0)
		{
			hld.update(u, u, node::lazy_container(0, x, 0));
		}
		else
		{
			cout << hld.query(u, x) << "\n";
		}
	}

	return 0;
}
