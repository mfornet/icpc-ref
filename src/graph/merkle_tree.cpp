/*
	Merkle tree is a tree in which each node is labeled with
	the hash of its subtree

	Notes: ans[u] is the hash of the tree rooted at u

	Complexity: O(n log n)

	Tested: https://www.spoj.com/problems/TREEISO/
*/

namespace merkle_tree
{
	using namespace multihash;

	void get(vector<mhash> &v)
	{
		sort(v.begin(), v.end()-1);
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
		vector<vector<mhash>> h(n), ch(n), rh(n);

		function<void(int, int)> dfs1 = [&](int u, int p)
		{
			for (auto v : adj[u])
				if (v != p)
				{
					dfs1(v, u);
					sz[u] += sz[v];
					h[u].push_back(h[v].back());
				}
			h[u].push_back({ sz[u], sz[u] });
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
					ch[v] = h[v];
					pos = lower_bound(rh[u].begin(), rh[u].end()-1, h[v].back()) - rh[u].begin();
					h[u].back() = (pos ? h[u][pos-1] : Z) + (h[u].end()[-2] - h[u][pos]) * iB[1]
										+ (mhash){sz[u], sz[u]} * B[h[u].size()-2];
					rget(h[v]);
					h[v].back() = h[u].back();
					h[v].push_back({ sz[v], sz[v] });
					get(h[v]);

					dfs2(v, u);

					h[u].back() = h[u].end()[-2] + rh[u].back() * B[h[u].size()-1];
					h[v] = ch[v];
					sz[v] = n - sz[u];
					sz[u] = n;
				}
		};
		dfs2(0, -1);
		return ans;
	}
}