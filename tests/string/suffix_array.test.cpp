#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/string/suffix_array.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	cin >> s;
	suffix_array sa(s.begin(), s.end());
	int n = sa.sa.size();
	for (int i = 1; i < n; ++i)
		cout << sa.sa[i] << " \n"[i+1==n];

	return 0;
}
