template<typename T>
struct rmq
{
	vector<vector<T>> dp;
	rmq(vector<T> &a)
	{
		int n = a.size(), lg = __lg(n);
		dp.resize(lg+1, vector<T>(n));
		dp[0] = a;
		for (int j = 1; j <= lg; ++j)
			for (int i = 0; i + (1<<j) <= n; ++i)
				dp[j][i] = min(dp[j-1][i], dp[j-1][i+(1<<(j-1))]);
	}

	inline T query(int a, int b) // [a, b)
	{
		int l = __lg(b - a);
		return min(dp[l][a], dp[l][b-(1<<l)]);
	}
};

template<typename T>
struct rmq_2D
{
	vector<vector<vector<vector<T>>>> dp;
	rmq_2D(vector<vector<T>> &a)
	{
		int n = a.size(), m = a[0].size(), lgn = __lg(n), lgm = __lg(m);
		dp.resize(lgn+1, vector<vector<vector<T>>>(lgm+1, vector<vector<T>>(n, vector<T>(m))));
		dp[0][0] = a;
		for (int x = 0; x <= lgn; ++x)
			for (int y = !x; y <= lgm; ++y)
				for (int i = 0; i + (1<<x) <= n; ++i)
					for (int j = 0; j + (1<<y) <= m; ++j)
						dp[x][y][i][j] = y > 0
							? max(dp[x][y-1][i][j], dp[x][y-1][i][j+(1<<(y-1))])
							: max(dp[x-1][y][i][j], dp[x-1][y][i+(1<<(x-1))][j]);
	}

	inline T query(int a, int b, int c, int d) // [a, b) * [c, d)
	{
		int x = __lg(b - a), y = __lg(d - c);
		return max({ dp[x][y][a][c], dp[x][y][a][d-(1<<y)], dp[x][y][b-(1<<x)][c], dp[x][y][b-(1<<x)][d-(1<<y)] });
	}
};
