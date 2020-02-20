struct treap
{
	struct node
	{
		node *ch[2];
		int key, prio, sz, acum[26], lazy;
		bool rev;

		node(int key) : key(key)
		{
			ch[0] = ch[1] = NULL;
			memset(acum, 0, sizeof acum);
			lazy = -1;
			rev = false;
			acum[key] = sz = 1;
			prio = rand();
		}
	}*root;

	node* new_node(int key)
	{
		return new node(key);
	}

	int size(node *u)
	{
		return u ? u->sz : 0;
	}

	int getC(node *u, int c)
	{
		return u ? u->acum[c] : 0;
	}

	void push(node *u)
	{
		if(!u)
			return;

		if (u->rev)
		{
			swap(u->ch[0], u->ch[1]);
			for (int i = 0; i < 2; ++i)
				if (u->ch[i])
					u->ch[i]->rev ^= true;
		}

		if (u->lazy != -1)
			for (int i = 0; i < 2; ++i)
				if (u->ch[i])
				{
					memset(u->ch[i]->acum, 0, sizeof u->ch[i]->acum);
					u->ch[i]->acum[u->lazy] = u->ch[i]->sz;
					u->ch[i]->lazy = u->ch[i]->key = u->lazy;
				}

		u->lazy = -1;
		u->rev = false;
	}

	node* update(node *u)
	{
		if (u)
		{
			u->sz = size(u->ch[0]) + size(u->ch[1]) + 1;

			for (int i = 0; i < 26; ++i)
				u->acum[i] = getC(u->ch[0], i) + getC(u->ch[1], i);

			++u->acum[u->key];
		}
		return u;
	}

	pair<node*, node*> split(node* u, int k)
	{// split for the kth first elements
		push(u);

		if (!u)
			return { u, u };

		if (size(u->ch[0]) >= k)
		{
			auto s = split(u->ch[0], k);
			u->ch[0] = s.second;
			return { s.first, update(u) };
		}

		auto s = split(u->ch[1], k - size(u->ch[0]) - 1);
		u->ch[1] = s.first;
		return { update(u), s.second };
	}

	node* merge(node *u, node *v)
	{
		push(u), push(v);

		if (!u || !v)
			return u ? u : v;

		if (u->prio > v->prio)
		{
			u->ch[1] = merge(u->ch[1], v);
			return update(u);
		}

		v->ch[0] = merge(u, v->ch[0]);
		return update(v);
	}

	treap() : root(NULL) {}
};
