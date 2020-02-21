#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

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
	fenwick<ll> f(n);
	for (int i = 0, x; i < n; ++i)
	{
		cin >> x;
		f.update(i, x);
	}
	for (int op, l, r; q--; )
	{
		cin >> op >> l >> r;
		if (op == 1)
			cout << f.query(r-1) - f.query(l-1) << "\n";
		else
			f.update(l, r);
	}

	return 0;
}
