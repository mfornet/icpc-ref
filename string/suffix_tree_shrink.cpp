template<typename T>
struct suffix_tree
{
	const static int inf = 2e9;
	vector<T> s;
	vector<map<T, int>> next;
	vector<int> spos, len, link;
	int node, pos, last;

	ll distinct;												// shrink
	int node2, pos2, leaves;
	vector<int> parent;

	suffix_tree() { make_node(0), node = pos = distinct = node2 = pos2 = leaves = 0; }

	int make_node(int p, int f = 0, int l = inf)
	{
		spos.push_back(p);
		parent.push_back(f);
		len.push_back(l);
		link.push_back(0);
		next.emplace_back();
		return spos.size()-1;
	}

	void extend(T c)
	{
		distinct += leaves; 									// add

		for (s.push_back(c), pos++, ++pos2, last = 0; pos > 0; )// update maximal suffix
		{
			int n = s.size();
			while (pos > len[next[node][s[n - pos]]])
				node = next[node][s[n - pos]], pos -= len[node];

			T edge = s[n - pos];
			int v = next[node][edge];
			T t = s[spos[v] + pos - 1];

			if (v == 0)
			{
				v = make_node(n - pos, node);
				distinct += get_len(v);  						// add
				++leaves;										// leaf
				link[last] = node;
				last = 0;
			}
			else if (t == c)
			{
				link[last] = node;
				return;
			}
			else
			{
				int u = make_node(spos[v], node, pos - 1);
				next[u][c] = spos.size(), make_node(n - 1, u);
				distinct += get_len(next[u][c]);				// add
				++leaves;										// leaf
				next[u][t] = v;
				spos[v] += pos - 1;
				len[v] -= (len[v] != inf) * (pos - 1);
				parent[v] = u;									// parent
				v = last = link[last] = u;
			}
			next[node][edge] = v;
			if (node == 0)
				pos--;
			else
				node = link[node];
		}
	}

	void shrink()
	{
		int n = s.size(), v = -1;

		if (pos != 0)
		{
			while (pos > len[next[node][s[n - pos]]])
				node = next[node][s[n - pos]], pos -= len[node];

			T edge = s[n - pos];
			v = next[node][edge];
		}

		while (pos2 > len[next[node2][s[n - pos2]]])
			node2 = next[node2][s[n - pos2]], pos2 -= len[node2];

		T edge2 = s[n - pos2];
		int v2 = next[node2][edge2];

		if (v == v2)
		{
			distinct -= pos2 - pos;
			spos[v2] += pos2 - pos;

			if (node == 0)
				pos--;
			else
				node = link[node];
		}
		else
		{
			distinct -= get_len(v2);
			next[node2].erase(edge2);
			--leaves;

			if (node2 != 0 && next[node2].size() == 1)
			{
				if (v != -1 && node == node2)
				{
					pos += get_len(node);
					node = parent[node];
				}
				int ch = next[node2].begin()->S;
				spos[ch] -= get_len(node2);
				len[ch] += (len[ch] != inf) * get_len(node2);
				next[parent[ch] = parent[node2]][s[spos[node2]]] = ch;
				next[node2].clear();
			}
		}

		if (node2 == 0)
			pos2--;
		else
			node2 = link[node2];
	}

	int get_len(int p) { return p == 0 ? 0 : min(len[p], (int)s.size()-spos[p]); }
};
