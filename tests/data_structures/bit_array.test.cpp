#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_3_C"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/bit_array.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	bit_array<1, 40> b({ n });
	const int sh = 1e9;
	for (int i = 0, x; i < n; ++i)
	{
		cin >> x;
		b.set({i}, x + sh);
	}
	int q;
	cin >> q;
	for (int l, r, x; q--; )
	{
		cin >> l >> r >> x;
		int ans = 0;
		for (; l < r; ++l)
			ans += b.get({l}) == x + sh;
		cout << ans << "\n";
	}

	return 0;
}
