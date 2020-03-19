/*
	Merkle tree is a tree in which each node is labeled with
	the hash of its subtree

	Notes: ans[u] is the hash of the tree rooted at u
	** Rolling Hashing is bad for hash a tree, see merkle_tree2 **

	Complexity: O(n log n)
*/

namespace merkle_tree
{
	using namespace multihash;

	void get(vector<mhash> &v, bool sorted = false)
	{
		if (!sorted) sort(v.begin(), v.end()-1);
		int n = v.size();
		for (int i = 1; i < n; ++i)
			v[i] = v[i-1] + v[i] * B[i];
	}

	void rget(vector<mhash> &v)
	{
		int n = v.size();
		for (int i = n-1; i > 0; --i)
			v[i] = (v[i] - v[i-1]) * iB[i];
	}

	vector<mhash> solve(const vector<vector<int>> &adj)
	{
		int n = adj.size(), pos;
		vector<int> sz(n, 1);
		vector<mhash> ch(n);
		vector<vector<mhash>> h(n), rh(n);

		function<void(int, int)> dfs1 = [&](int u, int p)
		{
			for (auto v : adj[u])
				if (v != p)
				{
					dfs1(v, u);
					sz[u] += sz[v];
					h[u].push_back(h[v].back());
				}
			h[u].push_back(to_mhash(sz[u]));
			get(h[u]);
		};
		dfs1(0, -1);

		vector<mhash> ans(n);
		function<void(int, int)> dfs2 = [&](int u, int p)
		{
			ans[u] = h[u].back();
			rh[u] = h[u];
			rget(rh[u]);

			for (auto v : adj[u])
				if (v != p)
				{
					sz[u] -= sz[v];
					sz[v] = n;
					ch[v] = h[v].back();
					pos = lower_bound(rh[u].begin(), rh[u].end()-1, h[v].back()) - rh[u].begin();
					h[u].back() = (pos ? h[u][pos-1] : Z) + (h[u].end()[-2] - h[u][pos]) * iB[1]
										+ to_mhash(sz[u]) * B[h[u].size()-2];
					rget(h[v]);
					h[v].back().fill(sz[v]);
					h[v].insert(lower_bound(h[v].begin(), h[v].end()-1, h[u].back()), h[u].back());
					get(h[v], true);

					dfs2(v, u);

					h[u].back() = h[u].end()[-2] + rh[u].back() * B[h[u].size()-1];
					h[v].back() = ch[v];
					sz[v] = n - sz[u];
					sz[u] = n;
				}
		};
		dfs2(0, -1);
		return ans;
	}
}

/*
	Complexity: O(n log mod) per module used
*/

namespace merkle_tree2
{
    using namespace multihash;
    vector<int> mask;

    vector<mhash> solve(const vector<vector<int>> &adj)
    {
        int n = adj.size();
        vector<pair<int, bool>> d(n);
        vector<mhash> h(n), ans(n);
        const int mx = *min_element(M.begin(), M.end());
        while (mask.size() < n)
            mask.push_back(randint(0, mx));

        auto f = [&](int u, int p)
        {
            d[u].F = 0, d[u].S = false;
            for (auto v : adj[u])
                if (v != p)
                {
                    if (d[v].F + 1 > d[u].F) d[u].F = d[v].F + 1, d[u].S = true;
                    else if (d[v].F + 1 == d[u].F) d[u].S = false;
                }
            h[u].fill(1);
            for (auto v : adj[u])
                if (v != p)
                    h[u] = h[u] * (h[v] + to_mhash(mask[d[u].F]));
        };

        function<void(int, int)> dfs1 = [&](int u, int p)
        {
            for (auto v : adj[u])
                if (v != p)
                    dfs1(v, u);
            f(u, p);
        };
        dfs1(0, -1);

        function<void(int, int)> dfs2 = [&](int u, int p)
        {
            ans[u] = h[u];
            for (auto v : adj[u])
                if (v != p)
                {                    
                    auto du = d[u];
                    auto dv = d[v];
                    mhash hu = h[u];
                    mhash hv = h[v];

                    if (d[u].F == d[v].F + 1 && d[u].S) f(u, v);
                    else h[u] = h[u] * inv(h[v] + to_mhash(mask[d[u].F]));

                    f(v, -1);

                    dfs2(v, u);

                    d[u] = du;
                    d[v] = dv;
                    h[u] = hu;
                    h[v] = hv;
                }
        };
        dfs2(0, -1);
        return ans;
    }
}