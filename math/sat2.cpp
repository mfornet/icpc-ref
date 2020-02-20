struct satisfiability_twosat
{
	satisfiability_twosat(int n) : n(n), imp(2 * n) {}

	inline int neg(int u) const { return ~u; }

	inline void add_implication(int u, int v)
	{
		if (u == v) return;
		imp[u+n].emplace_back(v+n);
		imp[~v+n].emplace_back(~u+n);
	}

	inline void add_clause(int u, int v) { add_implication(neg(u), v); }

	vector<bool> solve() const
	{
		vector<int> S, B, I(2 * n);
		function<void(int, int&)> dfs = [&](int u, int &t)
		{
			B.push_back(I[u] = S.size());
			S.push_back(u);
			for (int v : imp[u])
				if (!I[v]) dfs(v, t);
				else while (I[v] < B.back()) B.pop_back();
			if (I[u] == B.back())
				for (B.pop_back(), ++t; I[u] < S.size(); S.pop_back())
					I[S.back()] = t;
		};
		for (int u = 0, t = 2 * n; u < 2 * n; ++u)
			if (!I[u]) dfs(u, t);
		vector<bool> value(n);
		for (int i = 0; i < n; ++i)
			if (I[i+n] == I[~i+n]) return vector<bool>();
			else value[i] = I[i+n] < I[~i+n];
		return value;
	}

private:
	int n;
	vector<vector<int>> imp;
};


struct satisfiability_twosat
{
	satisfiability_twosat(int n) : n(n), imp(2 * n) {}

	inline int neg(int u) const { return ~u; }

	inline void add_implication(int u, int v)
	{
		if (u == v) return;
		imp[u+n].emplace_back(v+n);
		imp[~v+n].emplace_back(~u+n);
	}

	inline void add_clause(int u, int v) { add_implication(neg(u), v); }

	vector<bool> solve() const
	{
		vector<int> S, B, I(2 * n, -1), ord, edge(2 * n, -1);

		auto run = [&](int &t)
		{
			while (!ord.empty())
			{
				int u = ord.back();
				ord.pop_back();

				if (edge[u] == -1)
				{
					B.push_back(I[u] = S.size());
					S.push_back(u);
				}

				bool done = true;
				while (++edge[u] < imp[u].size())
				{
					int v = imp[u][edge[u]];
					if (!~I[v])
					{
						ord.emplace_back(u);
						ord.emplace_back(v);
						done = false;
						break;
					}
					else while (I[v] < B.back()) B.pop_back();
				}

				if (done && I[u] == B.back())
				{
					B.pop_back();
					++t;

					while (I[u] < (int) S.size())
					{
						I[S.back()] = t;
						S.pop_back();
					}
				}
			}
		};

		for (int u = 0, t = 2 * n; u < 2 * n; ++u)
			if (!~I[u])
			{
				ord.emplace_back(u);
				run(t);
			}
		vector<bool> value(n);
		for (int i = 0; i < n; ++i)
			if (I[i+n] == I[~i+n]) return vector<bool>();
			else value[i] = I[i+n] < I[~i+n];
		return value;
	}

private:
	int n;
	vector<vector<int>> imp;
};
