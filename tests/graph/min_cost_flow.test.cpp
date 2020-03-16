#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/min_cost_flow.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m, f;
	cin >> n >> m >> f;
	min_cost_flow<int> mcf(n+1);
	for (int i = 0, u, v, x, c; i < m; ++i)
	{
		cin >> u >> v >> x >> c;
		mcf.add_edge(u, v, x, c);
	}
	mcf.add_edge(n, 0, f, 0);
	auto ans = mcf.max_flow(n, n-1);
	if (ans.F != f)
	{
		cout << "-1\n";
		return 0;
	}
	cout << ans.S << "\n";

	return 0;
}
