/*
	Longest increasing subsequnece (LIS)

	Notes: returns the positions of a LIS

	Complexity: O(n log n)
*/

template<typename T>
vector<int> lis(const vector<T> &a)
{
	if (a.empty()) return {};
	vector<T> l; vector<int> who(a.size()), where(a.size());
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