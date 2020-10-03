#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/bipartite_matching.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int l, r, m;
	cin >> l >> r >> m;
	hopcroft_karp g(l, r);
	for (int i = 0, u, v; i < m; ++i)
	{
		cin >> u >> v;
		g.add_edge(u, v);
	}

	cout << g.max_matching() << "\n";
	for (int i = 0; i < l; ++i)
		if (g.mu[i] != -1)
			cout << i << " " << g.mu[i] << "\n";

	return 0;
}
