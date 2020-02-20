// returns (d, x, y) such that d = gcd(a, b) = ax + by
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
	if (b == 0) { x = 1, y = 0; return a; }
	ll r = extended_euclid(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

// returns (x, y) such that c = ax + by
pair<ll, ll> diophantine_equation(ll a, ll b, ll c)
{
	ll g, x, y;
	g = extended_euclid(a, b, x, y);
	ll k = 0; // k e Z
	return { x * c / g + (k * b / g), y * c / g - (k * a / g) };
}

// returns how many (x, y) exists such that x1<=x<=x2, y1<=y<=y2, c = ax + by
ll x1, x2, y1, y2;
ll diophantine_equation(ll a, ll b, ll c)
{
	ll g, x, y;
	g = extended_euclid(a, b, x, y);
	
	if (c % g != 0) return 0;
	if(g * b < 0) swap(x1, x2);
	if(g * a > 0) swap(y1, y2);

	return max((min((ll)floor(ld(x2 * g - x * c) / b), (ll)floor(ld(y2 * g - y * c) / -a))
			- max((ll)ceil(ld(x1 * g - x * c) / b), (ll)ceil(ld(y1 * g - y * c) / -a)) + 1), 0LL);
}