#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"

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
	ll x, sub, vsub;
	int prio, sprio;

	node2() : splay_tree() { x = sub = vsub = 0; prio = sprio = 2e9; }

	friend int get_prio(node2* u) { return u ? u->sprio : 2e9; }

	void update() override
	{
		splay_tree::update();
		sub = x + vsub;
		sub += (ch[0] ? ch[0]->sub : 0);
		sub += (ch[1] ? ch[1]->sub : 0);
		sprio = min({ prio, get_prio(ch[0]), get_prio(ch[1]) });
	}

	void update_vsub(node2* v, bool add)
	{
		vsub += (add ? +1 : -1) * v->sub;
	}

	void push() override
	{
		splay_tree::push();
	}

	node2* find()
	{
		assert(sprio < 1e9);
		node2* u = this;
		u->push();
		while (u->prio != u->sprio)
			u = u->ch[get_prio(u->ch[1]) == u->sprio], u->push();
		u->splay();
		return u;
	}
};

struct info
{
	int op, u, v, prio;
	info() : prio(1e9) {}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	link_cut_tree<node2> lct(2*n);
	for (int i = 0, x; i < n; ++i)
		cin >> x, lct[i]->x = x, lct[i]->update();
	vector<info> a(q);
	map<pair<int, int>, info*> mp;
	for (auto &i : a)
	{
		cin >> i.op >> i.u;
		if (i.op != 3) cin >> i.v;
		if (i.op < 2 && i.u > i.v) swap(i.u, i.v);
		if (i.op == 0)
			mp[{ i.u, i.v }] = &i;
		if (i.op == 1)
			mp[{ i.u, i.v }]->prio = &i-&a[0];
	}

	vector<pair<node2*, node2*>> record(2*n);
	set<int> free;
	for (int i = n; i < 2*n; ++i)
		free.insert(i);

	for (auto i : a)
	{
		if (i.op == 0)
		{
			auto u = lct[i.u];
			auto v = lct[i.v];

			if (lct.connected(u, v))
			{
				auto l = lct.lca(u, v);
				lct.access(u);
				l->splay();
				int priou = get_prio(l->ch[1]);
				lct.access(v);
				l->splay();
				int priov = get_prio(l->ch[1]);
				if (priov < priou) swap(u, v);

				lct.access(u);
				l->splay();
				assert(l->ch[1]);
				if (get_prio(l->ch[1]) < i.prio)
				{
					auto c = l->ch[1]->find();
					lct.cut(c, record[lct[c]].F);
					lct.cut(c, record[lct[c]].S);
					c->prio = 2e9;
					c->update();
					free.insert(lct[c]);
				}
				else
					continue;
			}

			auto c = lct[*free.begin()];
			record[*free.begin()] = { u, v };
			free.erase(free.begin());
			c->prio = i.prio;
			c->update();
			lct.link(u, c);
			lct.link(c, v);
			continue;
		}
		if (i.op == 1)
		{
			auto u = lct[i.u];
			auto v = lct[i.v];

			auto l = lct.lca(u, v);
			if (l != u) swap(u, v);
			if (l == u && lct.depth(u) + 2 == lct.depth(v))
			{
				auto c = lct.ancestor(v, 1);
				lct.cut(c, record[lct[c]].F);
				lct.cut(c, record[lct[c]].S);
				c->prio = 2e9;
				c->update();
				free.insert(lct[c]);
			}
			continue;
		}
		if (i.op == 2)
		{
			lct.access(lct[i.u]);
			lct[i.u]->x += i.v;
			lct[i.u]->update();
			continue;
		}
		if (i.op == 3)
		{
			cout << lct.get_root(lct[i.u])->sub << "\n";
		}
	}

	return 0;
}
