#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/dynamic_programming/lis.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i;
	auto ans = lis(a);
	for (size_t i = 1; i < ans.size(); ++i)
		assert(a[ans[i-1]] < a[ans[i]]);
	cout << ans.size() << "\n";

	return 0;
}
