#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/dominator_tree.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m, s;
	cin >> n >> m >> s;
	vector<vector<int>> g(n);
	for (int u, v; m--; )
	{
		cin >> u >> v;
		g[u].push_back(v);
	}
	auto ans = dominators(g, s);
	ans[s] = s;
	for (auto &i : ans)
		cout << i << " \n"[&i==&ans.back()];

	return 0;
}
