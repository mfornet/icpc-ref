#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/wavelet_matrix.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &i : a) cin >> i;
	wavelet_matrix<int, bit_array_vec> wm(a);
	for (int l, r, k; q--; )
	{
		cin >> l >> r >> k;
		cout << wm.quantile(l, r, k) << "\n";
	}

	return 0;
}
