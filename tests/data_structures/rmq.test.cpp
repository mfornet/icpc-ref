#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/rmq.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &i : a) cin >> i;
	rmq<int> R(a);
	for (int l, r; q--; )
	{
		cin >> l >> r;
		cout << R.query(l, r) << "\n";
	}

	return 0;
}
