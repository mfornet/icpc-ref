#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/union_find.cpp"
#include "../../src/geometry/rectilinear_mst.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<point> a(n);
	for (auto &i : a)
	{
		int x, y;
		cin >> x >> y;
		i = { x, y };
	}

	auto ans = rectilinear_mst(a);
	cout << ans.F << "\n";
	for (auto &i : ans.S)
		cout << i.F << " " << i.S << "\n";

	return 0;
}
