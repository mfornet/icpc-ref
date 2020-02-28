#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A"
//#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/geometry/rectangle_union.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<rectangle> v(n);
	for (auto &i : v)
	{
		cin >> i.xl >> i.yl >> i.xh >> i.yh;
	}
	cout << rectangle_area(v) << "\n";

	return 0;
}
