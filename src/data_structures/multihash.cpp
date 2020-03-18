namespace multihash
{
	const int D = 2, N = 1e6+5;
	typedef array<int, D> mhash;
	mhash B[N], iB[N], M, Z;

	mhash operator+(mhash lhs, const mhash &rhs)
	{
		for (int i = 0; i < D; ++i)
		{
			lhs[i] += rhs[i];
			if (lhs[i] >= M[i]) lhs[i] -= M[i];
		}
		return lhs;
	}

	mhash operator-(mhash lhs, const mhash &rhs)
	{
		for (int i = 0; i < D; ++i)
		{
			lhs[i] -= rhs[i];
			if (lhs[i] < 0) lhs[i] += M[i];
		}
		return lhs;
	}

	mhash operator*(mhash lhs, const mhash &rhs)
	{
		for (int i = 0; i < D; ++i)
			lhs[i] = (ll)lhs[i] * rhs[i] % M[i];
		return lhs;
	}

	mhash pow(mhash lhs, ll b)
	{
		mhash x; x.fill(1);
		for (; b > 0; b >>= 1)
		{
			if (b&1) x = x * lhs;
			lhs = lhs * lhs;
		}
		return x;
	}

	mhash to_mhash(int x)
	{
		mhash m;
		m.fill(x);
		return m;
	}

	void init(const mhash &b, const mhash &m)
	{
		M = m, B[1] = b, Z.fill(0), B[0].fill(1), iB[0].fill(1);
		for (int i = 0; i < D; ++i)
			iB[1][i] = pow_mod(B[1][i], M[i]-2, M[i]);
		for (int i = 2; i < N; ++i)
		{
			B[i] = B[i-1] * B[1];
			iB[i] = iB[i-1] * iB[1];
		}
	}
} 
