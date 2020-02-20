template<typename T>
struct minimum_aborescense
{
	struct edge { int src, dst; T weight; };
	vector<edge> edges;

	void add_edge(int u, int v, T w)
	{
		edges.push_back({ u, v, w });
	}

	T solve(int n, int r)
	{
		for (T res = 0;;)
		{
			vector<edge> in(n, { -1, -1, numeric_limits<T>::max() });
			for (auto e : edges) // cheapest comming edges
				if (in[e.dst].weight > e.weight)
					in[e.dst] = e;

			in[r] = {r, r, 0};
			for (int u = 0; u < n; res += in[u].weight, ++u)
				if (in[u].src < 0) return numeric_limits<T>::max(); // no comming edge => no aborescense

			int index = 0, sz = 0;
			vector<int> C(n, -1), mark(n, -1);

			for (int i = 0, u = 0; i < n; u = ++i) // contract cycles
			{
				if (mark[i] != -1) continue;

				while (mark[u] == -1)
					mark[u] = i, u = in[u].src;

				if (mark[u] != i || u == r) continue;

				for (int v = in[u].src; u != v; C[v] = index, v = in[v].src) ;
				C[u] = index++;
			}

			if (index == 0) return res; // found arborescence

			for (int i = 0; i < n; ++i) // contract
				if (C[i] == -1) C[i] = index++;

			for (auto &e : edges)
				if (C[e.src] != C[e.dst] && C[e.dst] != C[r])
					edges[sz++] = { C[e.src], C[e.dst], e.weight - in[e.dst].weight };

			edges.resize(sz), n = index, r = C[r];
		}
	}
};