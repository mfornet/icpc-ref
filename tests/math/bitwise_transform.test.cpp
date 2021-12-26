#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/number_theory/modular_arithmetics.cpp"
#include "../../src/math/bitwise_transform.cpp"

int main()
{
	#ifdef TurnRed
		//freopen("a.in", "r", stdin);
		//freopen("a.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(0), cin.tie(0);

	const int mod = 998244353;
	int n;
	cin >> n;
	n = 1<<n;
	vector<int> a(n), b(n);
	for (auto &i : a) cin >> i;
	for (auto &i : b) cin >> i;

	vector<int> bp(n);
	for (int i = 1; i < n; ++i)
		bp[i] = __builtin_popcount(i);

	vector<vector<int>> sa(21, vector<int>(n)), sb = sa;
	for (int i = 0; i < n; ++i)
	{
		sa[bp[i]][i] = a[i];
		sb[bp[i]][i] = b[i];
	}

	for (int i = 0; i < 21; ++i)
	{
		bitwise_transform::transform<OR, mod>(sa[i].data(), n);
		bitwise_transform::transform<OR, mod>(sb[i].data(), n);
	}

	vector<int> ans(n);
	for (int i = 0; i < 21; ++i)
	{
		vector<int> c(n);
		for (int j = 0; j <= i; ++j)
			for (int k = 0; k < n; ++k)
				c[k] = (c[k] + (ll)sa[j][k] * sb[i-j][k]) % mod;

		bitwise_transform::transform<OR, mod, true>(c.data(), n);
		for (int k = 0; k < n; ++k)
			if (bp[k] == i)
				ans[k] = c[k];
	}

	for (auto &i : ans)
		cout << i << " \n"[&i==&ans.back()];

	return 0;
}
