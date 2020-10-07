#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"

#include <bits/stdc++.h>

using namespace std;

#ifdef NeverBeRed
#include "debug.h"
#else
#define debug(...) 9715
#endif
typedef long long ll;
typedef long double ld;
typedef complex<ld> point;
#define F first
#define S second

#include "../../src/data_structures/union_find.cpp"
#include "../../src/graph/arborescence.cpp"

int main()
{
	#ifdef TurnRed
		//freopen("a.in", "r", stdin);
		//freopen("a.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m, root;
	cin >> n >> m >> root;

	vector<edge<ll>> e;
	for (int i = 0, u, v, w; i < m; ++i)
	{
		cin >> u >> v >> w;
		e.push_back({ u, v, w });
	}

	auto ans = min_arborescence(e, n, root);
	assert(ans.S[root] == -1);
	vector<vector<int>> adj(n);
	cout << ans.F << "\n";
	for (auto &i : ans.S)
		cout << (i == -1 ? root : e[i].src) << " \n"[&i==&ans.S.back()];

	return 0;
}
