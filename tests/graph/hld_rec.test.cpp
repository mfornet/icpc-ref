#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

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
	heavy_light_decomposition<segment_tree<node>> hld(n);
	vector<int> a(n);
	for (auto &i : a) cin >> i;
	for (int v = 1, u; v < n; ++v)
	{
		cin >> u;
		hld.add_edge(u, v);
	}
	
	hld.rootify_rec();
	for (int i = 0; i < n; ++i)
		hld.update(i, 0, node::lazy_container(0, a[i], 0));
	
	for (int t, u, x; q--; )
	{
		cin >> t >> u;
		if (t == 0)
		{
			cin >> x;
			hld.update(u, 0, node::lazy_container(0, x, 0));
		}
		else
		{
			cout << hld.query(u, u) << "\n";
		}
	}

	return 0;
}
