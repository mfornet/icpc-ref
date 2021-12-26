#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/number_theory/modular_arithmetics.cpp"
#include "../../src/math/linear_recurrence.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i;

	a = linear_recurrence::berlekamp_massey(a, 998244353);
	cout << a.size() << "\n";
	for (auto &i : a)
		cout << i << " \n"[&i==&a.back()];

	return 0;
}
