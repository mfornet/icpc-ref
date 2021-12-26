#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_2_B"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
//typedef complex<ll> point;
#define F first
#define S second

#define double ld
#include "../../src/math/fast_fourier_transform.cpp"
#include "../../src/number_theory/big_integer.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	bigint a, b;
	cin >> a >> b;
	cout << a - b << "\n";

	return 0;
}
