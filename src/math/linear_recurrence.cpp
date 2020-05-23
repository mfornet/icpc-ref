/*
	Linear Recurrence Solver

	Description: Consider
	x[i+n] = a[n-1] x[i] + a[n-2] x[i+1] + ... + a[0] x[i+n-1]
	with initial solution x[0], x[1], ..., x[n-1]
	
	get_kth compute k-th term of x
	Complexity: O(n^2)
	Tested: SPOJ REC

	Berlekamp Massey find (the shortest) linear recurrence relation
	(a[0], a[1], ...) given the initial values (x[0], x[1], ..., x[n-1])
	Complexity: O(n^2)
*/

namespace linear_recurrence
{
	vector<int> berlekamp_massey(const vector<int> &x, const int mod)
	{
		vector<int> ls, cur;
		for (int i = 0, lf, ld, xsz = x.size(); i < xsz; ++i)
		{
			int t = 0;
			for (size_t j = 0; j < cur.size(); ++j)
				t = (t + (ll)x[i - j - 1] * cur[j]) % mod;

			if ((t - x[i]) % mod == 0) continue;

			if (cur.empty())
			{
				cur.resize(i + 1);
				lf = i;
				ld = (t - x[i]) % mod;
				continue;
			}

			int k = -(ll)(x[i] - t) * pow_mod(ld, mod - 2, mod) % mod;
			vector<int> c(i - lf - 1);
			c.push_back(k);
			for (auto j : ls) c.push_back(-(ll)j * k % mod);
			c.resize(max(c.size(), cur.size()));

			for (size_t j = 0; j < cur.size(); ++j)
				c[j] = (c[j] + cur[j]) % mod;

			if (i - lf + (int)ls.size() >= (int)cur.size())
				ls = move(cur), lf = i, ld = (t - x[i]) % mod;

			cur = move(c);
		}
		for (auto &i : cur) i = (i + mod) % mod;
		return cur;
	}

	int get_kth(const vector<int> &a, const vector<int> &x, ll k, const int mod)
	{
		int m = a.size();
		vector<int> s(m), t(m);
		s[0] = 1;
		if (m != 1) t[1] = 1;
		else t[0] = a[0];

		auto mul = [&a, &mod](const vector<int> &v, const vector<int> &w)
		{
			int m = v.size();
			vector<int> t(2 * m);
			for (int j = 0; j < m; ++j)
				for (int k = 0; k < m; ++k)
					t[j + k] = (t[j + k] + (ll)v[j] * w[k]) % mod;

			for (int j = 2 * m - 1; j >= m; --j)
				for (int k = 1; k <= m; ++k)
					t[j - k] = (t[j - k] + (ll)t[j] * a[k - 1]) % mod;

			t.resize(m);
			return t;
		};

		for (; k > 0; k >>= 1)
		{
			if (k & 1) s = mul(s, t);
			t = mul(t, t);
		}

		int ret = 0;
		for (int i = 0; i < m; ++i)
			ret = (ret + (ll)s[i] * x[i]) % mod;
		return ret;
	}

	int guess_kth_term(const vector<int> &x, ll k, const int mod)
	{
		if (k < (int)x.size()) return x[k];
		vector<int> a = berlekamp_massey(x, mod);
		if (a.empty()) return 0;
		return get_kth(a, x, k, mod);
	}
}