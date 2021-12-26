#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/li_chao_tree.cpp"

ll dot(point a, point b)
{
	return real(conj(a) * b);
}

vector<ll> b;

struct side
{
	point p;
	side() : p(0, 2e18+5) {}
	side(point x) : p(x) {}

	inline static ll f(side s, ll x)
	{
		return dot(s.p, { b[x], 1LL });
	}
};

struct que
{
	ll t, a, b;
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, q;
	cin >> n >> q;
	vector<pair<ll, ll>> a(n);
	for (auto &i : a) cin >> i.F >> i.S, b.push_back(i.F);
	vector<que> qs(q);
	for (auto &i : qs) { cin >> i.t >> i.a; if (!i.t) cin >> i.b; b.push_back(i.a); }
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	auto get = [&](ll x)
	{
		return lower_bound(b.begin(), b.end(), x) - b.begin();
	};

	li_chao_tree<side> st(b.size());
	for (auto i : a)
		st.update(0, 0, b.size(), side({ i.F, i.S }));

	for (auto i : qs)
	{
		if (!i.t)
			st.update(0, 0, b.size(), side({ i.a, i.b }));
		else
			cout << st.query(0, 0, b.size(), get(i.a)) << "\n";
	}

	return 0;
}
