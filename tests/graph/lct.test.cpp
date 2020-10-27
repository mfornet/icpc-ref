#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/link_cut_tree.cpp"

struct node2 : splay_tree<node2*>
{
	ll val, sval;

	node2() : splay_tree() {  }

	friend ll get_val(node2* u) { return u ? u->sval : 0; }

	void update() override
	{
		splay_tree::update();
		sval = val + get_val(ch[0]) + get_val(ch[1]);
	}

	void update_vsub(node2* v, bool add) {}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	link_cut_tree<node2> lct(n);
	for (int i = 0, x; i < n; ++i)
		cin >> x, lct[i]->val = x, lct[i]->update();
	for (int i = 1, u, v; i < n; ++i)
	{
		cin >> u >> v;
		lct.link(lct[u], lct[v]);
	}
	for (int op, u, v, w, x; q--; )
	{
		cin >> op;
		if (op == 0)
		{
			cin >> u >> v >> w >> x;
			lct.cut(lct[u], lct[v]);
			lct.link(lct[w], lct[x]);
		}
		if (op == 1)
		{
			cin >> u >> w;
			auto p = lct[u];
			lct.access(p);
			p->val += w;
			p->update();
		}
		if (op == 2)
		{
			cin >> u >> v;
			lct.make_root(lct[u]);
			lct.access(lct[v]);
			cout << get_val(lct[v]->ch[0]) + lct[v]->val << "\n";
		}
	}

	return 0;
}
