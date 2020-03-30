/*
	Longest increasing subsequnece (LIS)

	Notes: returns the positions of a LIS

	Complexity: O(n log n)
*/
template<typename T>
vector<int> lis(const vector<T> &a)
{
	vector<T> l;
	for (auto &i : a)
	{
		auto it = lower_bound(l.begin(), l.end(), i) - l.begin();
		if (it == l.size()) l.emplace_back();
		l[it] = i;
	}

	vector<int> ans;
	for (int i = 0, p = 0; p < l.size(); ++i)
		if (a[i] == l[p])
			ans.push_back(i), ++p;

	return ans;
}

vector<int> lis_old(const vector<int> &a)
{
	vector<int> l, who(a.size()), where(a.size());
	for (auto &i : a)
	{
		auto it = lower_bound(l.begin(), l.end(), i) - l.begin();
		where[&i-&a[0]] = !it ? -1 : who[it-1];
		if (it == l.size()) l.emplace_back();
		l[it] = i, who[it] = &i-&a[0];
	}

	vector<int> ans;
	for (int p = who[l.size()-1]; p != -1; p = where[p])
		ans.push_back(p);

	reverse(ans.begin(), ans.end());
	return ans;
}