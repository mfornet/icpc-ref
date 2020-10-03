#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

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

#include "../../src/graph/gabow_edmonds.cpp"

int main()
{
	#ifdef TurnRed
		//freopen("a.in", "r", stdin);
		//freopen("a.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	graph g(n);
	for (int i = 0, u, v; i < m; ++i)
	{
		cin >> u >> v;
		g.add_edge(u, v);
	}

	cout << g.maximum_matching() << "\n";
	for (int i = 0; i < n; ++i)
		if (i < g.mate[i])
			cout << i << " " << g.mate[i] << "\n";

	return 0;
}
