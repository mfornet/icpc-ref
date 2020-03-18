/*
	Fast Fourier Transform

	Notes: fft_core function doesn't normalize when 
	    call it with sign=-1, you must do it be yourself,
	    implementing your own point is much faster
	    ** #define double ld if you have precision issues (probably for n around 5e5) **

	Complexity: O(n log n)
*/

namespace fft
{
	typedef complex<double> point;

	 // n must be a power of 2, sign must be +1 or -1
	void fft_core(point a[], int n, int sign = +1)
	{
		const double theta = 8 * sign * atan(static_cast<point::value_type>(1.0)) / n; 
		for (int i = 0, j = 1; j < n - 1; ++j)
		{
			for (int k = n >> 1; k > (i ^= k); k >>= 1);
			if (j < i) swap(a[i], a[j]);
		}
		for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
			for (int i = 0, irev = 0; i < n; i += m)
			{
				point w = exp(point(0, theta * irev));
				for (int k = n >> 2; k > (irev ^= k); k >>= 1);
				for (int j = i; j < mh + i; ++j)
				{
					int k = j + mh;
					point x = a[j] - a[k];
					a[j] += a[k];
					a[k] = w * x;
				}
			}
	}

	// Compute ffts of two integer arrays doing 1 fft instead of 2 ffts
	// n must be a power of 2
	template<typename T>
	pair<vector<point>, vector<point>> ffts(const vector<T> &a, const vector<T> &b, int n)
	{
		assert(n >= 1 && (n & (n - 1)) == 0);
		vector<point> p(n), pa(n), pb(n);
		for (int i = 0; i < n; ++i)
			p[i] = point(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
		fft_core(p.data(), n, +1);
		for (int i = 0; i < n; ++i)
		{
			int j = (n - i) & (n - 1);
			point u = p[i], v = conj(p[j]);
			pa[i] = (u + v) * point(0.5, +0.0);
			pb[i] = (u - v) * point(0.0, -0.5);
		}
		return make_pair(move(pa), move(pb));
	}

	typedef long long ll;

	// this only works if intermediate values are less than 10^15
	vector<ll> convolve(const vector<int> &a, const vector<int> &b)
	{
		int n = a.size() + b.size() - 1, m = 1;
		while (m < n) m *= 2;
		vector<point> pa, pb;
		tie(pa, pb) = ffts(a, b, m);
		for (int i = 0; i < m; ++i)
		{
			pa[i] /= m;
			pa[i] *= pb[i];
		}
		fft_core(pa.data(), m, -1);
		vector<ll> ans(n);
		for (int i = 0; i < n; ++i)
			ans[i] = llround(real(pa[i]));
		return ans;
	}

	// mod < 2^31
	vector<int> convolve(const vector<int> &a, const vector<int> &b, int mod)
	{
		int n = a.size() + b.size() - 1;
		for (int k : {1, 2, 4, 8, 16}) n |= (n >> k); ++n;
		vector<point> pa(n), pb(n);
		for (int i = 0; i < n; ++i)
		{
			if (i < a.size()) pa[i] = point(a[i] >> 15, a[i] & ((1 << 15) - 1));
			if (i < b.size()) pb[i] = point(b[i] >> 15, b[i] & ((1 << 15) - 1));
		}
		fft_core(pa.data(), n, +1);
		fft_core(pb.data(), n, +1);
		vector<point> c(n), d(n);
		for (int i = 0; i < n; ++i)
		{
			int j = (n - i) & (n - 1);
			point u = (pa[i] + conj(pa[j])) * point(0.5, +0.0);
			point v = (pa[i] - conj(pa[j])) * point(0.0, -0.5);
			point x = (pb[i] + conj(pb[j])) * point(0.5, +0.0);
			point y = (pb[i] - conj(pb[j])) * point(0.0, -0.5);
			c[i] = u * (x + y * point(0, 1));
			d[i] = v * (x + y * point(0, 1));
			c[i] /= n; d[i] /= n;
		}
		fft_core(c.data(), n, -1);
		fft_core(d.data(), n, -1);
		vector<int> ans(a.size() + b.size() - 1);
		for (int i = 0; i < (int) ans.size(); ++i)
		{
			int u = llround(real(c[i])) % mod;
			int v = llround(imag(c[i])) % mod;
			int x = llround(real(d[i])) % mod;
			int y = llround(imag(d[i])) % mod;
			ans[i] = ((ll) u * (1 << 30) % mod + (ll) (v + x) * (1 << 15) % mod + y) % mod;
		}
		return ans;
	}
}