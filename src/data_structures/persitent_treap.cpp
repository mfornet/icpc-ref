template<typename T>
struct treap
{
	struct node
	{
		T key;
		int prio, sz;
		node *ch[2];

		node(T Key, int Prio = rand(), int Sz = 1, node *u = NULL, node *v = NULL)
		{
			key = Key, prio = Prio, sz = Sz, ch[0] = u, ch[1] = v;
		}
	};

	node* clone(node *u)
	{
		return new node(u->key, u->prio, u->sz, u->ch[0], u->ch[1]);
	}

	int size(node *u)
	{
		return !u ? 0 : u->sz;
	}

	node* update(node *u)
	{
		u->sz = size(u->ch[0]) + size(u->ch[1]) + 1;
		return u;
	}

	node* rotate(node *u, bool d)
	{
		if (u->ch[d]->prio <= u->prio)
			return update(u);

		node *v = clone(u->ch[d]);
		u->ch[d] = v->ch[!d];
		v->ch[!d] = update(u);
		return update(v);
	}

	node* insert(node *u, T key)
	{
		if (!u)
			return new node(key);

		node *c = clone(u);
		bool d = key > u->key;
		c->ch[d] = insert(c->ch[d], key);
		return rotate(c, d);
	}

	node* erase(node *u, T key)
	{
		if (!u)
			return u;

		node *c = clone(u);

		if (u->key == key)
		{
			if (!u->ch[0] || !u->ch[1])
				return u->ch[!u->ch[0]];
			bool d = rand() & 1;
			node *v = u->ch[d];
			while (v->ch[!d] != NULL) v = v->ch[!d];
			c->key = v->key;							// copy all that you need from v
			c->ch[d] = erase(c->ch[d], c->key);
			return update(c);
		}

		bool d = c->key < key;
		c->ch[d] = erase(c->ch[d], key);
		return update(c);
	}

	pair<node*, node*> split(node* u, int k)
	{// split for the kth first elements
		if (!u)
			return { u, u };

		node *c = clone(u);
		if (size(c->ch[0]) >= k)
		{
			auto s = split(c->ch[0], k);
			c->ch[0] = s.second;
			return { s.first, update(c) };
		}

		auto s = split(c->ch[1], k - size(c->ch[0]) - 1);
		c->ch[1] = s.first;
		return { update(c), s.second };
	}

	node* merge(node *u, node *v)
	{
		if (!u || !v)
			return u ? u : v;

		if (u->prio > v->prio)
		{
			node *c = clone(u);
			c->ch[1] = merge(c->ch[1], v);
			return update(c);
		}

		node *c = clone(v);
		c->ch[0] = merge(u, c->ch[0]);
		return update(c);
	}

	int less(node *u, T key)
	{
		if (!u)
			return 0;
		if (u->key < key)
			return size(u->ch[0]) + 1 + less(u->ch[1], key);
		return less(u->ch[0], key);
	}

	node* kth(node *u, int k)
	{
		if (!u || size(u->ch[0]) + 1 == k)
			return u;
		if (size(u->ch[0]) >= k)
			return kth(u->ch[0], k);
		return kth(u->ch[1], k - size(u->ch[0]) - 1);
	}

	node* insert2(node *u, T key)
	{
		auto s = split(u, less(u, key));
		return merge(merge(s.first, new node(key)), s.second);
	}

	node* erase2(node *u, T key)
	{
		auto s = split(u, less(u, key)), s2 = split(s.second, 1);
		if (s2.first && s2.first->key == key)
			return merge(s.first, s2.second);
		return u;
	}
};
