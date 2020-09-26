#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/link_cut_tree.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;

	link_cut_tree<node_sub_sum> lct(n);
	for (int i = 0, x; i < n; ++i)
	{
		cin >> x;
		lct[i]->apply(x);
	}

	for (int i = 1, u, v; i < n; ++i)
	{
		cin >> u >> v;
		lct.link(lct[u], lct[v]);
	}

	for (int t, u, v, w, x; q--; )
	{
		cin >> t;
		if (t == 0)
		{
			cin >> u >> v >> w >> x;
			lct.cut(lct[u], lct[v]);
			lct.link(lct[w], lct[x]);
		}
		if (t == 1)
		{
			cin >> v >> u >> w;
			lct.make_root(lct[u]);
			lct.cut(lct[v]);
			lct[v]->apply(w);
			lct.link(lct[u], lct[v]);
		}
		if (t == 2)
		{
			cin >> v >> u;
			lct.make_root(lct[u]);
			lct.cut(lct[v]);
			cout << lct[v]->sub << "\n";
			lct.link(lct[u], lct[v]);
		}
	}

	return 0;
}
