#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/abi.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	fenwick<ll> f(n+1);
	for (int op, x, l, r; q--; )
	{
		cin >> op >> l;
		if (op == 1)
			cout << f.query(l-1) << "\n";
		else
			cin >> r >> x, f.update(l-1, x), f.update(r, -x);
	}

	return 0;
}
