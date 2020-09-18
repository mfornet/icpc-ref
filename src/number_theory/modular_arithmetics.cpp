/*
	Modular arithmetics (long long)

	Note:
		int       < 2^31 < 10^9
		long long < 2^63 < 10^18
	feasible for M < 2^62 (10^18 < 2^62 < 10^19)

	Tested: SPOJ
*/

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

// inverse of 1, 2, ..., n mod P in O(n) (P must be prime)
vector<ll> inverses(int n, int P)
{
	vector<ll> inv(n+1, 1);
	for (int i = 2; i <= n; ++i)
		inv[i] = inv[P%i] * (P-P/i) % P;
	return inv;
}

template<typename T, typename U>
T pow_mod(T a, U b, int mod)
{
	T r = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1) r = (ll)r * a % mod;
		a = (ll)a * a % mod;
	}
	return r;
}

namespace combinatorics
{
	const int mod = 998244353, N = 2e5+5; // mod must be prime
	int fac[N], ifac[N];

	void init()
	{
		fac[0] = ifac[0] = 1;
		for (int i = 1; i < N; ++i)
		{
			fac[i] = (ll)fac[i-1] * i % mod;
			ifac[i] = pow_mod(fac[i], mod-2, mod);
		}
	}

	int comb(int n, int k)
	{
		return (ll)fac[n] * ifac[n-k] % mod * ifac[k] % mod;
	}

	// n objects to be placed into k(possible empty) bins
	int starsandbars(int n, int k)
	{
		return comb(n+k-1, k-1);
	}

	// partitions of an n element set into k non-empty sets
	int stirling(int n, int k) // (2nd kind)
	{
		int r = 0;
		for (int i = 0; i < k; ++i)
			r = (r + ((i&1) ? -1 : +1) * (ll)comb(k, i) * pow_mod(k-i, n, mod)) % mod;
		return ((ll)r + mod) % mod * ifac[k] % mod;
	}
}

ll inv(ll b, ll M)
{
	ll u = 1, x = 0, s = b, t = M;
	while (s)
	{
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	return (x %= M) >= 0 ? x : (x + M);
}

// solve a x == b (mod M) (sol iff (a, m) | b same as (a, m) | (b, m))
ll div(ll a, ll b, ll M)
{
	ll u = 1, x = 0, s = a, t = M;
	while (s)
	{
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	if (b % t) return -1; // infeasible
	return (x < 0 ? (x + M) : x) * (b / t) % M;
}

// Modular Matrix
mat zeros(int n)
{
	return mat(n, vec(n));
}

mat eye(int n)
{
	mat I(n, vec(n));
	for (int i = 0; i < n; ++i)
		I[i][i] = 1;
	return I;
}

mat mul(mat &A, mat &B, ll M)
{
	int l = A.size(), m = B.size(), n = B[0].size();
	mat C(l, vec(n));
	for (int i = 0; i < l; ++i)
		for (int k = 0; k < m; ++k)
			for (int j = 0; j < n; ++j)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
	return C;
}

mat pow(mat A, ll b, ll M)
{
	mat X = eye(A.size());
	for (; b > 0; b >>= 1)
	{
		if (b & 1) X = mul(X, A, M);
		A = mul(A, A, M);
	}
	return X;
}

// assume: M is prime (singular ==>
// verify: SPOJ9832
mat inv(mat A, ll M)
{
	int n = A.size();
	mat B(n, vec(n));
	for (int i = 0; i < n; ++i)
		B[i][i] = 1;

	for (int i = 0; i < n; ++i)
	{
		int j = i;
		while (j < n && A[j][i] == 0) ++j;
		if (j == n)
			return {};
		swap(A[i], A[j]);
		swap(B[i], B[j]);
		ll inv = div(1, A[i][i], M);
		for (int k = i; k < n; ++k)
			A[i][k] = A[i][k] * inv % M;
		for (int k = 0; k < n; ++k)
			B[i][k] = B[i][k] * inv % M;
		for (int j = 0; j < n; ++j)
		{
			if (i == j || A[j][i] == 0)
				continue;
			ll cor = A[j][i];
			for (int k = i; k < n; ++k)
				A[j][k] = (A[j][k] - cor * A[i][k] % M + M) % M;
			for (int k = 0; k < n; ++k)
				B[j][k] = (B[j][k] - cor * B[i][k] % M + M) % M;
		}
	}

	return B;
}
