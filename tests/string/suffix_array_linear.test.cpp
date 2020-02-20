#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/string/suffix_array_linear.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	cin >> s;
	auto sa = suffix_array(s.begin(), s.end()).F;
	int n = sa.size();
	for (int i = 0; i < n; ++i)
		cout << sa[i] << " \n"[i+1==n];

	return 0;
}
