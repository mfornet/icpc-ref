#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/graph/dinic.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	dinic<int> d(n);
	for (int i = 0, u, v, x; i < m; ++i)
	{
		cin >> u >> v >> x;
		d.add_edge(u, v, x);
	}
	auto ans = d.max_flow(0, n-1);
	cout << ans << "\n";

	return 0;
}
