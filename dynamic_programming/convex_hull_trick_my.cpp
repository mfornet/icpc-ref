struct convex_hull_trick // upper_hull
{
	typedef complex<ll> T;
	ll dot(T a, T b) { return real(conj(a)*b); }
	ll cross(T a, T b) { return imag(conj(a)*b); }

	size_t pt = 0;
	vector<T> h;

	void add(T p)
	{
		while (h.size() >= 2 && cross(h.end()[-1] - h.end()[-2], p - h.end()[-2]) >= 0) h.pop_back();
		pt = min(pt, h.size());
		h.push_back(p);
	}

	ll get(T p)
	{
		int b = 0, e = h.size()-1;
		while (b < e)
		{
			int m = (b+e)>>1;
			if (dot(h[m]-h[m+1], p) <= 0)
				b = m+1;
			else
				e = m;
		}
		return dot(h[b], p);
	}

	ll get2(T p)
	{
		while (pt+1 < h.size() && dot(h[pt+1], p) >= dot(h[pt], p)) ++pt;
		return dot(h[pt], p);
	}
};