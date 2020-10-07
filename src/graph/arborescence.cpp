struct skew_heap
{
	struct node
	{
		node *l, *r;
		pair<ll, int> key;
		ll delta;
	} *root;

	skew_heap() : root(NULL) {}

	void prop(node *a)
	{
		a->key.F += a->delta;
		if (a->l) a->l->delta += a->delta;
		if (a->r) a->r->delta += a->delta;
		a->delta = 0;
	}

	node* merge(node *a, node *b)
	{
		if (!a || !b) return a ?: b;
		prop(a), prop(b);
		if (b->key.F < a->key.F) swap(a, b);
		swap(a->l, a->r = merge(b, a->r));
		return a;
	}

	void push(pair<ll, int> key)
	{
		node *n = new node();
		*n = { NULL, NULL, key, 0 };
		root = merge(root, n);
	}

	void pop()
	{
		prop(root);
		node *t = root;
		root = merge(root->l, root->r);
		delete t;
	}

	pair<ll, int> top() { return prop(root), root->key; }
	bool empty() { return !root; }
	void add(ll delta) { root->delta += delta; }
	void merge(skew_heap x) { root = merge(root, x.root); }
};

template<typename T>
struct edge
{
	int src, dst;
	T weight;
};

/*
	Notes: return cost, parent edge of each node (-1 for the root)

	Complexity: O(m log m)
*/

template<typename T>
pair<ll, vector<int>> min_arborescence(const vector<edge<T>> &edges, int n, int root)
{
	union_find uf(n);
	vector<skew_heap> heap(n);
	for (auto &e : edges)
		heap[e.dst].push({ e.weight, &e-&edges[0] });

	ll score = 0, weight;
	vector<int> seen(n, -1), parent(n, -1), prev_edge(edges.size()), order, cycle;
	seen[root] = root;
	for (int s = 0, in_cycle = 0, i; s < n; ++s)
	{
		vector<int> path;
		for (int u = s, v, w; seen[u] < 0; u = uf.root(v))
		{
			path.push_back(u);
			seen[u] = s;
			if (heap[u].empty()) return { numeric_limits<ll>::max(), {} };

			tie(weight, i) = heap[u].top();
			score += weight;
			heap[u].add(-weight);
			heap[u].pop();

			order.push_back(i);
			if (parent[edges[i].dst] == -1)
				parent[edges[i].dst] = i;
			for (; in_cycle; --in_cycle, cycle.pop_back())
				prev_edge[cycle.back()] = i;
			cycle.push_back(i);

			if (seen[v = uf.root(edges[i].src)] == s)
			{
				skew_heap new_heap;
				do
				{
					w = path.back();
					path.pop_back();
					new_heap.merge(heap[w]);
					++in_cycle;
				} while (uf.join(v, w));
				heap[uf.root(v)] = new_heap;
				seen[uf.root(v)] = -1;
			}
		}
	}

	reverse(order.begin(), order.end());
	vector<bool> used(edges.size());
	for (auto i : order)
		if (!used[i])
		{
			for (int j = parent[edges[i].dst]; j != i; j = prev_edge[j])
				used[j] = true;
			parent[edges[i].dst] = i;
		}

	return { score, parent };
}
