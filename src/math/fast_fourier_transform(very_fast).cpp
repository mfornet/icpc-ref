/*
	Fast Fourier Transform

	Notes: fft_core function doesn't normalize when 
	    call it with sign=-1, you must do it be yourself
	    ** #define double ld if you have precision issues (probably for n around 5e5) **

	Complexity: O(n log n)
*/

// using point = complex<double>;
struct point
{
	typedef double value_type;
	double x, y;

	point(double x = 0, double y = 0) : x(x), y(y) {}
	point& operator+=(const point &rhs) { x += rhs.x, y += rhs.y; return *this; }
	point operator+(point rhs) const { return rhs += *this; }
	point operator-(const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
	point operator*(const point &rhs) const { return point(x * rhs.x - y * rhs.y, y * rhs.x + x * rhs.y); }
	point& operator/=(double db) { x /= db, y /= db; return *this; }
};

point conj(const point &p) { return point(p.x, -p.y); }
double real(const point &p) { return p.x; }
double imag(const point &p) { return p.y; }

namespace fft
{
	const double PI = atan2(static_cast<point::value_type>(0), static_cast<point::value_type>(-1));
	vector<int> rev;
	vector<point> roots = {{0, 0}, {1, 0}};

	void ensure_size(int bits)
	{
		const int n = 1 << bits;
		if (rev.size() >= n) return;

		rev.resize(n);
		for (int i = 1, j = 0; i < n - 1; ++i)
		{
			for (int k = n >> 1; (j ^= k) < k; k >>= 1);
			rev[i] = j;
		}
		rev[n - 1] = n - 1;
		int cur_bits = __lg(roots.size());
		roots.resize(n);
		roots[0] = 1;
		for (; cur_bits < bits; ++cur_bits)
		{
			const double theta = 2 * PI / (1 << (cur_bits + 1));
			for (int i = 1 << (cur_bits - 1); i < (1 << cur_bits); i++)
			{
				roots[i << 1] = roots[i];
				double angle_i = theta * (2 * i + 1 - (1 << cur_bits));
				double y = sin(angle_i), x = cos(angle_i);
				//sincos(angle_i, &y, &x);
				roots[(i << 1) + 1] = point(x, y);
			}
		}
	}

	// n must be a power of 2, sign must be +1 or -1
	void fft_core(point a[], int n, int sign = +1)
	{
		ensure_size(__lg(n));
		int shift = __lg(rev.size() / n);
		if (sign == -1) reverse(a + 1, a + n);
		for (int i = 1; i < n - 1; ++i)
		{
			int j = rev[i] >> shift;
			if (j < i) swap(a[i], a[j]);
		}
		for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
			for (int i = 0; i < n; i += m)
				for (int j = 0; j < mh; ++j)
				{
					point u = a[i + j + mh] * roots[mh + j];
					a[i + j + mh] = a[i + j] - u;
					a[i + j] = a[i + j] + u;
				}
	}

	using ll = long long;

	// Compute ffts of two real arrays doing 1 fft instead of 2 ffts
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
			pa[i] = pa[i] * pb[i];
		}
		fft_core(pa.data(), m, -1);
		vector<ll> ans(n);
		for (int i = 0; i < n; ++i)
			ans[i] = llround(real(pa[i]));
		return ans;
	}

	// mod < 2^31
	vector<int> convolve(const vector<int> &a, const vector<int> &b, int mod, bool equal = false)
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
		if (equal) copy(pa.begin(), pa.end(), pb.begin());
		else fft_core(pb.data(), n, +1);
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
};

// asume non-negative numbers
const int WIDTH = 5;
const ll RADIX = 100000; // = 10^WIDTH

vector<int> parse(const string &s)
{
	int n = s.length();
	int m = (n + WIDTH - 1) / WIDTH;
	vector<int> v(m);
	for (int i = 0; i < m; ++i)
	{
		int b = n - WIDTH * i, x = 0;
		for (int a = max(0, b - WIDTH); a < b; ++a)
			x = x * 10 + s[a] - '0';
		v[i] = x;
	}
	return v;
}

void print(vector<ll> v)
{
	int i, N = v.size();
	ll c = 0;
	for (i = 0; i < N; ++i)
	{
		c += v[i];
		v[i] = c % RADIX;
		c /= RADIX;
	}
	while (c > 0)
	{
		v.emplace_back(c % RADIX);
		c /= RADIX;
		++N;
	}
	for (i = N - 1; i > 0 && v[i] == 0; --i);
	cout << v[i];
	for (i--; i >= 0; i--)
		cout << setw(WIDTH) << setfill('0') << v[i];
	cout << endl;
}
