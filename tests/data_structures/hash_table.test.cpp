#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_4_D"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/hash_table.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	hash_table<int, int> h;
	vector<int> a;
	const int sh = 1e9;
	for (int i = 0, x; i < n; ++i)
	{
		cin >> x;
		if (h.find(x + sh) == NULL)
			a.push_back(x);
		else
			h.erase(x + sh);
		h.set(x + sh, x);
	}
	for (auto &i : a)
		cout << i << " \n"[&i==&a.back()];

	return 0;
}
