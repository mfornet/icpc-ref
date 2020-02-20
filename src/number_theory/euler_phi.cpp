typedef long long ll;

ll euler_phi(ll n)
{
	if (n == 0)
		return 0;
	ll ans = n;
	for (ll x = 2; x * x <= n; ++x)
		if (n % x == 0)
		{
			ans -= ans / x;
			while (n % x == 0)
				n /= x;
		}
	if (n > 1)
		ans -= ans / n;
	return ans;
}

// phi(n) for all n in [lo, hi)
vector<ll> euler_phi(ll lo, ll hi)
{
	vector<ll> ps = primes(sqrt(hi) + 1);
	vector<ll> res(hi - lo), phi(hi - lo, 1);
	iota(res.begin(), res.end(), lo);
	for (ll p : ps)
		for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p)
		{
			if (res[k - lo] < p)
				continue;
			phi[k - lo] *= (p - 1);
			res[k - lo] /= p;
			while (res[k - lo] > 1 && res[k - lo] % p == 0)
			{
				phi[k - lo] *= p;
				res[k - lo] /= p;
			}
		}
	for (ll k = lo; k < hi; ++k)
		if (res[k - lo] > 1)
			phi[k - lo] *= (res[k - lo] - 1);
	return phi; // phi[k-lo] = phi(k)
}

// Summatory function Phi(n) of the totient function phi(n)
ll f(int n)
{
	if (n >= M && !memo2.count(n)) memo2[n] = -1;
	ll &r = (n < M) ? memo[n] : memo2[n];

	if (r != -1) return r;

	r = (ll)n * (n+1) / 2;

	for (ll d = 1; d * d <= n; ++d)
	{
		if (d > 1)
			r -= f(n / d);
		if (d != n / d)
			r -= ((n / d) - (n / (d+1))) * f(d);
	}

	return r;
}