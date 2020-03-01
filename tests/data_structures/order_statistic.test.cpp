#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3117"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/order_statistic.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (auto &i : a) cin >> i, i -= k;
	int id = 0;
	ordered_set<pair<ll, int>> s;
	ll ans = 0, sum = 0;
	s.insert({ 0, -1 });
	for (auto i : a)
	{
		sum += i;
		ans += s.order_of_key({ sum, 1<<30 });
		s.insert({ sum, id++ });
	}
	cout << ans << "\n";

	return 0;
}
