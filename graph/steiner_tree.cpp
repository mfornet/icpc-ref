/*
	Steiner tree solution
	O(2**(k-1) * E log E + 3**(k-1) * V)
*/
template<typename R, typename T>
R steiner_tree(vector<vector<pair<int, T>>> &adj, vector<int> s)
{
	const R oo = numeric_limits<R>::max();
	int n = adj.size(), k = s.size() - 1;

	vector<vector<R>> dp(1<<k, vector<R>(n, oo));
	for (int i = 0; i < k; ++i)
		dp[1<<i][s[i]] = 0;

	priority_queue<pair<R, int>, vector<pair<R, int>>, greater<pair<R, int>>> pq;
	for (int m = 1, u; m < 1<<k; ++m)
	{
		for (u = 0; u < n; ++u)
		{
			for (int i = m; (i = (i-1)&m); )
				dp[m][u] = min(dp[m][u], dp[i][u] + dp[m^i][u]);

			if (dp[m][u] != oo)
				pq.push({ dp[m][u], u });
		}

		for (R w; !pq.empty(); )
		{
			tie(w, u) = pq.top(), pq.pop();
			if (w == dp[m][u])
				for (auto v : adj[u])
					if (w + v.S < dp[m][v.F])
						pq.push({ (dp[m][v.F] = w + v.S), v.F });
		}
	}

	return dp[(1<<k)-1][s.back()];
}

/*
	Steiner tree solution (only works for k <= 5 when the solution always form a Caterpillar tree)
	O(2**k * E log E + 2**k * k * V)
*/
template<typename R, typename T>
R spider_man(vector<vector<pair<int, T>>> &adj, vector<int> s)
{
	const R oo = numeric_limits<R>::max();
	int n = adj.size(), k = s.size();

	vector<vector<R>> dp(1<<k, vector<R>(n, oo));
	priority_queue<pair<R, int>, vector<pair<R, int>>, greater<pair<R, int>>> pq;
	for (int i = 0, u; i < k; ++i)
	{
		pq.push({ dp[1<<i][s[i]] = 0, s[i] });
		for (R w; !pq.empty(); )
		{
			tie(w, u) = pq.top(), pq.pop();
			if (w == dp[1<<i][u])
				for (auto v : adj[u])
					if (w + v.S < dp[1<<i][v.F])
						pq.push({ (dp[1<<i][v.F] = w + v.S), v.F });
		}
	}

	for (int m = 1, u; m < 1<<k; ++m)
	{
		for (u = 0; u < n; ++u)
			if (dp[m][u] != oo)
				pq.push({ dp[m][u], u });

		for (R w; !pq.empty(); )
		{
			tie(w, u) = pq.top(), pq.pop();
			if (w == dp[m][u])
			{
				for (auto v : adj[u])
					if (w + v.S < dp[m][v.F])
						pq.push({ (dp[m][v.F] = w + v.S), v.F });
				for (int v = 0; v < k; ++v)
					if (~m>>v&1)
						dp[m|1<<v][u] = min(dp[m|1<<v][u], dp[m][u] + dp[1<<v][u]);
			}
		}
	}

	return *min_element(dp[(1<<k)-1].begin(), dp[(1<<k)-1].end());
}