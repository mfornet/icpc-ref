#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/link_cut_tree.cpp"

const ll mod = 998244353;

struct node2 : splay_tree<node2*>
{
	using splay_tree::ch;
	ll a, b, c, d;

	node2() : splay_tree() {  }

	void update() override
	{
		splay_tree::update();
		if (ch[0]) ch[0]->push();
		if (ch[1]) ch[1]->push();
		c = a, d = b;
		if (ch[0]) tie(c, d) = make_pair(c * ch[0]->c % mod, (c * ch[0]->d + d) % mod);
		if (ch[1]) tie(c, d) = make_pair(ch[1]->c * c % mod, (ch[1]->c * d + ch[1]->d) % mod);
	}

	void update_vsub(node2* v, bool add) {}

	void push() override
	{
		if (splay_tree::rev)
		{
			splay_tree::push();
			update();
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	link_cut_tree<node2> lct(n);
	for (int i = 0, a, b; i < n; ++i)
		cin >> a >> b, lct[i]->a = a, lct[i]->b = b, lct[i]->update();
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
			cin >> u >> w >> x;
			auto p = lct[u];
			lct.access(p);
			p->a = w;
			p->b = x;
			p->update();
		}
		if (op == 2)
		{
			cin >> u >> v >> x;
			lct.make_root(lct[u]);
			auto p = lct[v];
			lct.access(p);
			auto ch1 = p->ch[1];
			p->ch[1] = NULL;
			p->update();
			cout << (p->c * x + p->d) % mod << "\n";
			p->ch[1] = ch1;
			p->update();
		}
	}

	return 0;
}
