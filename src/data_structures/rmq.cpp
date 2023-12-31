/*
	Static data structure for min/max queries

	Complexity: O(n log n) build, O(1) query
*/
template<typename T>
struct rmq
{
	vector<vector<T>> dp;
	rmq(vector<T> &a)
	{
		int n = a.size(), lg = __lg(n);
		dp.resize(lg+1, vector<T>(n));
		dp[0] = a;
		for (int j = 0; j < lg; ++j)
			for (int i = 0; i + (2<<j) <= n; ++i)
				dp[j+1][i] = min(dp[j][i], dp[j][i+(1<<j)]);
	}

	inline T query(int a, int b) // [a, b)
	{
		int l = __lg(b - a);
		return min(dp[l][a], dp[l][b-(1<<l)]);
	}
};
