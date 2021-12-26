const ld eps = 1e-12;
struct segment { point p, q; };
using line = segment;

ld dot(point a, point b) { return real(conj(a) * b); }
ld cross(point a, point b) { return imag(conj(a) * b); }

int ccw(const point &a, const point &b, const point &c)
{
	auto x = imag(conj(b - a) * (c - a));
	if (x > eps) return +1; // counter clockwise
	if (x < -eps) return -1; // clockwise
	return 0;
}

bool intersectSS(const segment &s, const segment &t)
{
	return ccw(s.p, s.q, t.p) * ccw(s.p, s.q, t.q) <= 0
			&& ccw(t.p, t.q, s.p) * ccw(t.p, t.q, s.q) <= 0;
}

point crosspoint(const line &l, const line &m)
{
	ld A = cross(l.q - l.p, m.q - m.p);
	ld B = cross(l.q - l.p, l.q - m.p);
	if (abs(A) < eps && abs(B) < eps)
		return m.p; // same line
	if (abs(A) < eps)
		assert(false); // !!!PRECONDITION NOT SATISFIED!!!
	return m.p + B / A * (m.q - m.p);
}

struct event
{
	point p;
	int i, j; // (-2, j) open, (-1, j) close, (i, j) intersection

	bool operator<(const event &e) const // actually >
	{
		if (abs(real(p) - real(e.p)) > eps)
			return real(p) > real(e.p);
		if (i >= 0 && e.i >= 0)
			return imag(p) > imag(e.p);
		return (i == -1 ? 2e9 : i) > (e.i == -1 ? 2e9 : e.i);
	}
};

/*
	Find all intersection points

	Complexity: O((n + k) log n)

	** vertical lines are not allowed **
	** infinite intersection points are not allowed
	   or find only one (don't use crosspoint) **
*/
vector<point> intersection(vector<segment> &v)
{
	if (v.empty()) return {};

	priority_queue<event> pq;
	for (auto &i : v)
	{
		int j = &i - &v[0];
		if (real(i.q) < real(i.p)) swap(i.p, i.q);
		pq.push({ i.p, -2, j }); // open
		pq.push({ i.q, -1, j }); // close
	}

	ld sx; // sweep position
	auto eval = [&](segment &i)
	{
		auto m = i.q - i.p;
		return imag(m) / real(m) * (sx - real(i.p)) + imag(i.p);
	};

	auto cmp = [&](int i, int j) { return eval(v[i]) - eval(v[j]) < -eps; };
	multiset<int, decltype(cmp)> s(cmp);

	vector<decltype(s)::iterator> pos(v.size(), s.end());
	vector<point> ans;
	vector<bool> alive(v.size(), true);
	vector<int> del;

	auto check = [&](auto i, auto j)
	{
		auto s1 = v[*i], s2 = v[*j];
		if (!intersectSS(s1, s2)) return;
 		auto p = crosspoint(s1, s2);
 		if (real(p) - sx > -eps)
 			pq.push({ p, *i, *j });
	};

	auto insert = [&](int i)
	{
		auto &it = pos[i];
		it = s.insert(i);
		if (it != s.begin()) check(prev(it), it);
		if (next(it) != s.end()) check(it, next(it));
	};

	auto rem = [&](int i)
	{
		if (pos[i] == s.end()) return;
		s.erase(pos[i]);
		pos[i] = s.end();
		del.push_back(i);
	};

	while (!pq.empty())
	{
		event e = pq.top();
		pq.pop();

		sx = real(e.p);
		if (!del.empty())
		{
			for (auto i : del)
				if (alive[i])
					insert(i);
			del.clear();
		}

		if (e.i == -2) // open
		{
			insert(e.j);
			continue;
		}

		if (e.i >= 0) // intersection
		{
			while (true)
			{
				ans.push_back(e.p); // found!!!
				rem(e.i), rem(e.j);
				while (true)
				{
					event e2 = pq.top();
					e2.p -= e.p;
					if (e2.i < 0 || abs(real(e2.p)) > eps || abs(imag(e2.p)) > eps)
						break;
					pq.pop();
					rem(e2.i), rem(e2.j);
				}
				if (pq.top().i < 0 || abs(real(pq.top().p) - real(e.p)) > eps)
					break;
				e = pq.top(), pq.pop();
			}

			if (abs(real(pq.top().p) - real(e.p)) > eps)
				continue;
			e = pq.top(), pq.pop();
		}

		while (true) // close
		{
			auto &it = pos[e.j];
			if (it != s.end())
			{
				if (it != s.begin() && next(it) != s.end()) check(prev(it), next(it));
				s.erase(it);
			}
			it = s.end();
			alive[e.j] = false;
			if (pq.empty() || pq.top().i != -1 || abs(real(pq.top().p) - real(e.p)) > eps)
				break;
			e = pq.top(), pq.pop();
		}
	}
	return ans;
}