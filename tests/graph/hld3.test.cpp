#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E"

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

	int n;
	cin >> n;
	heavy_light_decomposition<segment_tree<node, seg_lazy>, true> hld(n);
	for (int u = 0, v, k; u < n; ++u)
	{
		cin >> k;
		while (k--)
		{
			cin >> v;
			hld.add_edge(u, v);
		}
	}
	
	hld.rootify();
	
	int q;
	cin >> q;
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
			cout << hld.query(u, 0) << "\n";
		}
	}

	return 0;
}
