#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

int Pow(int a, int b, int mod)
{
	int x = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1) x = (ll)x * a % mod;
		a = (ll)a * a % mod;
	}
	return x;
}

#include "../../src/data_structures/multihash.cpp"
using namespace multihash;

vector<mhash> get(string s)
{
	int n = s.length();
	vector<mhash> h(n+1);
	h[0].fill(0);
	for (int i = 1; i <= n; ++i)
	{
		h[i].fill(s[i-1] + 1);
		h[i] = h[i-1] + h[i] * B[i];
	}
	return h;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	init({ 313, 433 }, { (int)1e9+7, (int)1e9+9 });
	string a, b;
	cin >> a >> b;

	int n = a.length(), m = b.length();
	auto ha = get(a);
	auto hb = get(b);
	for (int i = m; i <= n; ++i)
		if ((ha[i] - ha[i-m]) * iB[i-m] == hb.back())
			cout << i-m << "\n";

	return 0;
}
