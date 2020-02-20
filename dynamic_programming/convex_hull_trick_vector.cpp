// Semi-dynamic structure allowing add points and
// query for extreme point in a given direction
// Complexity: O(log n) amortized for insert
// and O(log^2 n) for query
// WARNING: be carefull with overflow when using
// with integers

template<typename T>
using Point = complex<T>;

template<typename T>
T cross(Point<T> a, Point<T> b) { return imag(conj(a) * b); }
template<typename T>
T dot(Point<T> a, Point<T> b) { return real(conj(a) * b); }

template<typename T, int turn>
struct half_hull
{
	using point = Point<T>;

	point extreme(const point &p) const
	{
		assert(!hulls.empty() && imag(p) * turn >= 0);
		auto pos = hulls.begin();
		while (pos->empty()) ++pos;
		point best = pos->extreme(p);
		while (++pos != hulls.end())
			if (!pos->empty())
			{
				point q = pos->extreme(p);
				if (dot(p, best - q) < 0)
					best = q;
			}
		return best;
	}

	void insert(const point &p)
	{
		hull h(1, p);
		for (auto pos = hulls.begin(); pos != hulls.end(); ++pos)
			if (pos->empty()) { h.swap(*pos); break; }
			else h = merge(h, *pos), pos->clear();
		if (!h.empty()) hulls.emplace_back(h);
	}

private:
	struct hull : vector<point>
	{
		using base = vector<point>;
		using base::base;
		using base::begin;
		using base::empty;
		using base::size;

		point extreme(const point &p) const
		{
			assert(!empty());
			auto lo = 0, hi = (int) size() - 1;
			while (lo < hi)
			{
				int mid = (lo + hi) / 2;
				if (dot(p, begin()[mid] - begin()[mid + 1]) <= 0)
					lo = mid + 1;
				else hi = mid;
			}
			return begin()[lo];
		}
	};

	static hull merge(const hull &lhs, const hull &rhs)
	{
		hull h;
		auto comp = [](const point &a, const point &b) {
			if (real(a) != real(b))
				return real(a) < real(b);
			return imag(a) < imag(b);
		};
		auto add_point = [&](const point &p) {
			while (h.size() >= 2 && turn * cross(h.end()[-1] - h.end()[-2], p - h.end()[-2]) >= 0)
				h.pop_back();
			h.emplace_back(p);
		};
		for (auto a = lhs.begin(), b = rhs.begin(); a != lhs.end() || b != rhs.end();)
			add_point(a == lhs.end() || (b != rhs.end() && comp(*b, *a)) ? *b++ : *a++);
		return h;
	}

	vector<hull> hulls;
};

template<typename T>
struct convex_hull_trick
{
	void insert(const complex<T> &p)
	{
		lower_hull.insert(p);
		upper_hull.insert(p);
	}

	complex<T> extreme(const complex<T> &p) const
	{
		if (std::imag(p) < 0)
			return lower_hull.extreme(p);
		return upper_hull.extreme(p);
	}

private:
	half_hull<T, +1> upper_hull;
	half_hull<T, -1> lower_hull;
};
