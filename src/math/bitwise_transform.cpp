/*
	AND, OR and XOR convolutions

	Notes: if you use mod make sure 0 <= a[i], b[i] < mod when you call convolve

	Complexity: O(n log n)
*/

enum bit_op { AND, OR, XOR };
namespace bitwise_transform
{
	template<int P, typename T>
	inline void fix(T &x)
	{
		if (x >= P) x -= P;
		else if (x < 0) x += P;
	}

	template<bit_op B, int P, bool inv = false, typename T>
	void transform(T a[], int n)
	{
		for (int len = 1; len < n; len <<= 1)
			for (int i = 0; i < n; i += len << 1)
				for (int j = i; j < i + len; ++j)
				{
					T u = a[j], v = a[j + len];
					if (B == AND) a[j] = v - u * inv, a[j + len] = u + v * (!inv);
					if (B == OR) a[j] = u * (!inv) + v, a[j + len] = u - inv * v;
					if (B == XOR) a[j] = u + v, a[j + len] = u - v;
					if (P != -1) fix<P>(a[j]), fix<P>(a[j + len]);
				}
		if (B == XOR && inv)
		{
			int in = pow_mod(n, P-2, P);
			for (int i = 0; i < n; ++i)
			{
				if (P == -1) a[i] /= n;
				else a[i] = (ll)a[i] * in % P;
			}
		}
	}

	template<bit_op B, int P = -1, typename T>
	vector<T> convolve(vector<T> a, vector<T> b)
	{
		int n = max(a.size(), b.size()), sz = 1;
		while (sz < n) sz <<= 1;
		a.resize(sz);
		b.resize(sz);
		transform<B, P>(a.data(), sz);
		transform<B, P>(b.data(), sz);
		for (int i = 0; i < sz; ++i)
		{
			a[i] *= b[i];
			if (P != -1) a[i] %= P;
		}
		transform<B, P, true>(a.data(), sz);
		return a;
	}
}