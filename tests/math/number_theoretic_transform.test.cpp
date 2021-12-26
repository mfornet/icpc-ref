#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/number_theory/modular_arithmetics.cpp"
#include "../../src/math/number_theoretic_transform.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (auto &i : a) cin >> i;
	for (auto &i : b) cin >> i;
	auto ans = ntt::convolve(a, b);
	for (auto &i : ans)
		cout << i << " \n"[&i==&ans.back()];

	return 0;
}
