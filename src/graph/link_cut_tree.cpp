template<class node>
struct link_cut_tree
{
	bool connected(node* u, node* v) { return lca(u, v) != NULL; }

	int depth(node* u)
	{
		access(u); return get_sz(u->ch[0]);
	}

	node* get_root(node* u)
	{
		access(u);
		while (u->ch[0]) u = u->ch[0], push(u);
		return access(u), u;
	}

	node* ancestor(node* u, int k)
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

	void cut(node* u, node* v)
	{
		//make_root(u); access(v); cut(v);
		cut(depth(u) > depth(v) ? u : v);
	}

	void make_root(node* u)
	{
		access(u);
		u->rev ^= 1;
		access(u);
		assert(!u->ch[0] && !u->ch[1]);
	}

	void access(node *u)
	{
		for (node* v = u, *pre = NULL; v; v = v->p)
		{
			v->splay(); // now switch virtual children
			//if (pre) v->vsub -= pre->sub;
			//if (v->ch[1]) v->vsub += v->ch[1]->sub;
			v->ch[1] = pre; v->update(); pre = v;
		}
		u->splay(); assert(!u->ch[1]); // right subtree is empty
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
		if (ch[0]) ch[0]->push();
		if (ch[1]) ch[1]->push();
		sz = 1 + get_sz(ch[0]) + get_sz(ch[1]);
	}

	virtual void push()
	{
		if (rev)
		{
			if (ch[0]) ch[0]->rev ^= 1;
			if (ch[1]) ch[1]->rev ^= 1;
			swap(ch[0], ch[1]); rev = 0;
		}
	}

	int dir()
	{
		if (!p) return -2;
		if (p->ch[0] == this) return 0;
		if (p->ch[1] == this) return 1;
		return -1;
	}

	bool is_root() { return dir() < 0; }

	friend void set_link(pnode u, pnode v, int d)
	{
		if (v) v->p = u;
		if (d >= 0) u->ch[d] = v;
	}

	void rotate()
	{
		assert(!is_root());
		int x = dir(); pnode g = p;
		set_link(g->p, static_cast<pnode>(this), g->dir());
		set_link(g, ch[x^1], x);
		set_link(static_cast<pnode>(this), g, x^1);
		g->update(); update();
	}

	void splay()
	{
		while (!is_root() && !p->is_root())
		{
			p->p->push(), p->push(), push();
			dir() == p->dir() ? p->rotate() : rotate();
			rotate();
		}
		if (!is_root()) p->push(), push(), rotate();
		push();
	}
};

struct node : splay_tree<node*>
{
	node() : splay_tree() {  }

	void update() override
	{
		splay_tree::update();
	}

	void push() override
	{
		splay_tree::push();
	}
};