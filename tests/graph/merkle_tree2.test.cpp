#define PROBLEM "https://www.hackerrank.com/contests/hourrank-21/challenges/tree-isomorphism/problem"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/useful/random.cpp"
#include "../../src/number_theory/modular_arithmetics.cpp"
#include "../../src/data_structures/union_find.cpp"
#include "../../src/data_structures/multihash.cpp"
#include "../../src/graph/merkle_tree.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	multihash::init({ 23, 13 }, { 14821, 17351 });
	using namespace multihash;

	int n;
	cin >> n;
	vector<pair<int, int>> edges(n-1);
	for (auto &i : edges) cin >> i.F >> i.S, --i.F, --i.S;

	vector<mhash> ans;
	for (int m = 1; m < 1<<(n-1); ++m)
	{
		int r;
		union_find uf(n);
		for (int i = 0; i < n-1; ++i)
			if (m >> i & 1)
				uf.join(edges[i].F, edges[i].S), r = edges[i].F;

		int x = uf.root(r);
		bool ok = true;
		for (int i = 0; i < n-1; ++i)
			if (m >> i & 1)
				ok &= uf.root(edges[i].F) == x;

		if (ok)
		{
			int t = 0;
			vector<int> id(n, -1);
			for (int i = 0; i < n-1; ++i)
				if (m >> i & 1)
				{
					if (id[edges[i].F] == -1) id[edges[i].F] = t++;
					if (id[edges[i].S] == -1) id[edges[i].S] = t++;
				}

			vector<vector<int>> adj(t);
			for (int i = 0; i < n-1; ++i)
				if (m >> i & 1)
				{
					adj[id[edges[i].F]].push_back(id[edges[i].S]);
					adj[id[edges[i].S]].push_back(id[edges[i].F]);
				}

			auto h = merkle_tree::solve(adj);
			ans.push_back(*min_element(h.begin(), h.end()));
		}
	}

	sort(ans.begin(), ans.end());
	cout << unique(ans.begin(), ans.end()) - ans.begin() + 1 << "\n";

	return 0;
}
