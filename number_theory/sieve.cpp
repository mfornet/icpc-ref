const int N = 1e6 + 5;
vector<int> p(N + 5);
for (ll i = 3; i <= N; i += 2)
    if (!p[i])
        for (ll j = i * i; j <= N; j += 2 * i)
            p[j] = i;

for (int i = 4; i <= N; i += 2)
	p[i] = 2;

vector<int> line_of_assambly(int N) // generate primes numbers O(N log N), sqrt(N) in memory
{
    vector<int> p(1, 2);
    set<pair<int, int>> S;
    S.insert( { 4, 2 });

    for (int i = 3; i < N; ++i)
    {
        auto it = S.lower_bound({ i, 0 });
        if (it->first > i)
        {
            p.push_back(i);
            if (i * i < N)
                S.insert( { i * i, 2LL * i });
        }
        else
            do
            {
                S.insert({ it->first + it->second, it->second });
                S.erase(it);
                it = S.lower_bound( { i, 0 });
            } while (it->first == i);
    }

    return p;
}

// primes in [lo, hi)
vector<ll> primes(ll lo, ll hi)
{
	const ll M = 1 << 14, SQR = 1 << 16;
	vector<bool> composite(M), small_composite(SQR);
	vector<pair<ll, ll>> sieve;
	for (ll i = 3; i < SQR; i += 2)
		if (!small_composite[i])
		{
			ll k = i * i + 2 * i * max(0.0, ceil((lo - i*i)/(2.0*i)));
			sieve.push_back({ 2 * i, k });
			for (ll j = i * i; j < SQR; j += 2 * i)
				small_composite[j] = 1;
		}
	vector<ll> ps;
	if (lo <= 2)
	{
		ps.push_back(2);
		lo = 3;
	}
	for (ll k = lo | 1, low = lo; low < hi; low += M)
	{
		ll high = min(low + M, hi);
		fill(composite.begin(), composite.end(), 0);
		for (auto &z : sieve)
			for (; z.second < high; z.second += z.first)
				composite[z.second - low] = 1;
		for (; k < high; k += 2)
			if (!composite[k - low])
				ps.push_back(k);
	}
	return ps;
}

vector<ll> primes(ll hi)
{
	return primes(0, hi);
}
