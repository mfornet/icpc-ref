#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/union_find.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	union_find uf(n);
	for (int t, u, v; q--; )
	{
		cin >> t >> u >> v;
		if (t == 0) uf.join(u, v);
		else cout << (uf.root(u) == uf.root(v)) << "\n";
	}

	return 0;
}
