template<typename charT, typename Container>
struct suffix_automaton
{
	const int npos = -1;

	struct node
	{
		int slink, length;
		Container next;
		node(int slink, int length) : slink(slink), length(length), next{{}} {}
		int operator[](const charT &c) const { return next[c]; }
		int& operator[](const charT &c) { return next[c]; }
	};

	suffix_automaton()
	{
		sink = 0;
		new_node();
	}

	int extend(const charT &c)
	{
		int p, q, np, nq;
		if (q = nodes[sink][c]) // not needed this block of code for a single string
		{
			if (nodes[q].length == 1 + nodes[sink].length)
				return sink = q;
			nq = new_node(nodes[q]);
			nodes[nq].length = 1 + nodes[sink].length;
			nodes[q].slink = nq;
			for (p = sink; p != npos && nodes[p][c] == q; p = nodes[p].slink)
				nodes[p][c] = nq;
			return sink = nq;
		}
		np = new_node();
		nodes[np].length = 1 + nodes[sink].length;
		for (p = sink; p != npos && !nodes[p][c]; p = nodes[p].slink)
			nodes[p][c] = np;
		if (p == npos)
			return nodes[np].slink = 0, sink = np;
		if (nodes[q = nodes[p][c]].length == 1 + nodes[p].length)
			return nodes[np].slink = q, sink = np;
		nq = new_node(nodes[q]);
		nodes[nq].length = 1 + nodes[p].length;
		nodes[q].slink = nodes[np].slink = nq;
		for (; p != npos && nodes[p][c] == q; p = nodes[p].slink)
			nodes[p][c] = nq;
		return sink = np;
	}

	inline void reset_sink() { sink = 0; }
	const node& operator[](int node_id) const { return nodes[node_id]; }

	vector<int> rev_top_sort() const
	{
		vector<int> ord(nodes.size());
		iota(ord.begin(), ord.end(), 0);
		int maxl = 0;
		for (auto &nod : nodes) maxl = max(maxl, nod.length);
		vector<int> bucket(maxl + 1);
		for (auto &nod : nodes) ++bucket[nod.length];
		partial_sum(bucket.begin(), bucket.end(), bucket.begin());
		for (int e = 0; e < nodes.size(); ++e)
			ord[--bucket[nodes[e].length]] = e;
		reverse(ord.begin(), ord.end());
		ord.pop_back(); // remove source
		return ord;
	}

	int size() const { return nodes.size(); }

private:
	int sink;
	vector<node> nodes;

	int new_node()
	{
		int _node = nodes.size();
		nodes.emplace_back(npos, 0);
		return _node;
	}

	int new_node(const node &nod)
	{
		int _node = nodes.size();
		nodes.push_back(nod);
		return _node;
	}
};
