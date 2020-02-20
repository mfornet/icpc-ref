bool find(set<pair<int, int>> &S, int x, int y)
{
	auto it = S.lower_bound({ x, y });
	return (it != S.end() && it->first <= x && it->second >= y)
			|| (it != S.begin() && (--it)->first <= x && it->second >= y);
}

void insert(set<pair<int, int>> &S, int x, int y)
{
	if (find(S, x, y))
		return;

	auto it = S.lower_bound({ x, y });
	while (it != S.end() && it->first >= x && it->second <= y)
		it = S.erase(it);

	it = S.insert({ x, y }).first;

	if (++it != S.end() && y + 1 >= it->first)
	{
		int t = it->second;
		S.erase({ x, y });
		S.erase(it);
		it = S.insert({ x, y = t }).first;
	}
	else --it;

	if (it != S.begin() && (--it)->second + 1 >= x)
	{
		int t = it->first;
		S.erase({ x, y });
		S.erase(it);
		S.insert({ x = t, y });
	}
}

void erase(set<pair<int, int>> &S, int x, int y)
{
	auto it = S.lower_bound({ x, y });
	while (it != S.end() && it->first >= x && it->second <= y)
		it = S.erase(it);

	it = S.lower_bound({ x, y });

	if (it != S.end() && y >= it->first)
	{
		int t = it->second;
		it = S.erase(it);
		if (y < t) it = S.insert({ y + 1, t }).first;
	}

	if (it != S.begin() && (--it)->second >= x)
	{
		auto t = *it;
		S.erase(it);
		if (t.first < x) S.insert({ t.first, x - 1 });
		if (y < t.second) S.insert({y + 1, t.second});
	}
}