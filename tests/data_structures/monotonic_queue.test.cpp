#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

#include "../../src/data_structures/monotonic_queue.cpp"

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, k;
	cin >> n >> k;

	monotonic_queue<int> mq;
	for (int i = 0, x; i < n; ++i)
	{
		cin >> x;
		mq.add(i, -x);
		mq.remove(i-k);
		if (i >= k-1) cout << -mq.max() << " \n"[i==n-1];
	}

	return 0;
}
