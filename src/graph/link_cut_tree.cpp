template<class node>
struct link_cut_tree
{
	bool connected(node* u, node* v) { return lca(u, v) != NULL; }

	int depth(node* u) { access(u); return get_sz(u->ch[0]); }

	node* get_root(node* u) // get root of LCT component
	{
		access(u);
		while (u->ch[0]) u = u->ch[0], u->push();
		return access(u), u;
	}

	node* ancestor(node* u, int k) // get k-th parent on path to root
	{
		k = depth(u) - k;
		assert(k >= 0);
		for (; ; u->push())
		{
			int sz = get_sz(u->ch[0]);
			if (sz == k) return access(u), u;
			if (sz < k) k -= sz+1, u = u->ch[1];
			else u = u->ch[0];
		}
		assert(0);
	}

	node* lca(node* u, node* v)
	{
		if (u == v) return u;
		access(u); access(v);
		if (!u->p) return NULL;
		u->splay(); return u->p ?: u;
	}

	void link(node* u, node* v) // make u parent of v
	{
		assert(!connected(u, v));
		make_root(v);
		access(u); set_link(v, u, 0); v->update();
	}

	void cut(node* u) // cut u from its parent
	{
		access(u);
		u->ch[0]->p = NULL;
		u->ch[0] = NULL;
		u->update();
	}

	void cut(node* u, node* v) // if u, v adj in tree
	{
		cut(depth(u) > depth(v) ? u : v);
	}

	void make_root(node* u) // make u root of LCT component
	{
		access(u);
		u->reverse();
		access(u);
		assert(!u->ch[0] && !u->ch[1]);
	}

	void access(node *u) // puts u on the preferred path, splay (right subtree is empty)
	{
		for (node* v = u, *pre = NULL; v; v = v->p)
		{
			v->splay(); // now update virtual children
			if (pre) v->update_vsub(pre, false);
			if (v->ch[1]) v->update_vsub(v->ch[1], true);
			v->ch[1] = pre; v->update(); pre = v;
		}
		u->splay(); assert(!u->ch[1]);
	}

	node* operator[](int i) { return &data[i]; }
	int operator[](node* i) { return i - &data[0]; }

	vector<node> data;
	link_cut_tree(int n) : data(n) {}
};

template<typename pnode>
struct splay_tree
{
	pnode ch[2], p;
	bool rev;
	int sz;

	splay_tree() { ch[0] = ch[1] = p = NULL; rev = 0; sz = 1; }

	friend int get_sz(pnode u) { return u ? u->sz : 0; }

	virtual void update()
	{
		sz = 1 + get_sz(ch[0]) + get_sz(ch[1]);
	}

	virtual void push()
	{
		if (rev)
		{
			if (ch[0]) ch[0]->reverse();
			if (ch[1]) ch[1]->reverse();
			rev = 0;
		}
	}

	virtual void reverse()
	{
		rev ^= 1;
		swap(ch[0], ch[1]);
	}

	int dir()
	{
		if (!p) return -2; // root of LCT component
		if (p->ch[0] == this) return 0; // left child
		if (p->ch[1] == this) return 1; // right child
		return -1; // root of current splay tree
	}

	bool is_root() { return dir() < 0; }

	friend void set_link(pnode u, pnode v, int d)
	{
		if (v) v->p = u;
		if (d >= 0) u->ch[d] = v;
	}

	void rotate() // assume p and p->p propagated
	{
		assert(!is_root());
		int x = dir(); pnode g = p;
		set_link(g->p, static_cast<pnode>(this), g->dir());
		set_link(g, ch[x^1], x);
		set_link(static_cast<pnode>(this), g, x^1);
		g->update(); //update();
	}

	void splay() // bring this to top of splay tree
	{
		while (!is_root() && !p->is_root())
		{
			p->p->push(), p->push(), push();
			dir() == p->dir() ? p->rotate() : rotate();
			rotate();
		}
		if (!is_root()) p->push(), push(), rotate();
		push(); update();
	}
};

// lazy should be I'm ok my childs are not ok (only affect childs)
// calling u->update require no lazy in u
// use reverse when the order of the childs matters (fix the node here)
struct node : splay_tree<node*>
{
	ll x, sub, vsub;

	node() : splay_tree() { x = sub = vsub = 0; }

	void update() override
	{
		splay_tree::update();
		sub = x + vsub;
		sub += (ch[0] ? ch[0]->sub : 0);
		sub += (ch[1] ? ch[1]->sub : 0);
	}

	void update_vsub(node* v, bool add)
	{
		vsub += (add ? +1 : -1) * v->sub;
	}

	void push() override
	{
		splay_tree::push();
	}

	void reverse() override
	{
		splay_tree::reverse();
	}
};

struct node_sub_sum : splay_tree<node_sub_sum*>
{
	int rsz, vrsz; ll x, sub, vsub, addsub, addvsub;

	node_sub_sum() : splay_tree() { x = vrsz = sub = vsub = addsub = addvsub = 0; rsz = 1; }

	void update() override
	{
		splay_tree::update();
		assert(addsub == 0);
		sub = x + vsub;
		rsz = 1 + vrsz;
		for (int i = 0; i < 2; ++i)
			if (ch[i])
				sub += ch[i]->sub, rsz += ch[i]->rsz;
	}

	void update_vsub(node_sub_sum* v, bool add)
	{
		if (!add) v->apply(addvsub);
		vsub += (add ? +1 : -1) * v->sub;
		vrsz += (add ? +1 : -1) * v->rsz;
		if (add) v->apply(-addvsub);
	}

	void push() override
	{
		splay_tree::push();
		if (addsub)
		{
			if (ch[0]) ch[0]->apply(addsub);
			if (ch[1]) ch[1]->apply(addsub);
			addsub = 0;
		}
	}

	void reverse() override
	{
		splay_tree::reverse();
	}

	void apply(ll i)
	{
		x += i;
		sub += (ll)i * rsz;
		vsub += (ll)i * vrsz;
		addsub += i;
		addvsub += i;
	}
};