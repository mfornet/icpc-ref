/*
	Compute for a string S the suffix array order and rank of every suffix starting in (0, 1, ..., |S|-1)	
	
	Complexity: O(|S|)
*/

void get_buckets(int *s, const int n, vector<int> &bkt, const int K, bool end)
{
	for (int i = 0; i < K; ++i) bkt[i] = 0;
	for (int i = 0; i < n; ++i) ++bkt[s[i]];
	for (int i = 0, sum = 0; i < K; ++i)
	{
		sum += bkt[i];
		bkt[i] = end ? sum : sum - bkt[i];
	}
}

void induce_sort(int *s, int *sa, const int n, const vector<bool> &type, vector<int> &bkt, const int K)
{
	get_buckets(s, n, bkt, K, false);
	for (int i = 0, j; i < n; ++i)
		if ((j = sa[i] - 1) >= 0 && !type[j]) sa[bkt[s[j]]++] = j;
	get_buckets(s, n, bkt, K, true);
	for (int i = n - 1, j; i >= 0; --i)
		if ((j = sa[i] - 1) >= 0 && type[j]) sa[--bkt[s[j]]] = j;
}

void sa_is(int *s, int *sa, const int n, vector<int> &bkt)
{
	vector<bool> type(n);
	type[n - 1] = true;
	for (int i = n - 3; i >= 0; --i)
		type[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && type[i + 1]);
	const int K = *max_element(s, s + n) + 1;
	get_buckets(s, n, bkt, K, true);
	for (int i = 0; i < n; ++i) sa[i] = -1;
	auto isLMS = [&](int i) { return i > 0 && type[i] && !type[i - 1]; };
	for (int i = 1; i < n; ++i)
		if (isLMS(i)) sa[--bkt[s[i]]] = i;
	induce_sort(s, sa, n, type, bkt, K);
	int n1 = 0;
	for (int i = 0; i < n; ++i)
		if (isLMS(sa[i])) sa[n1++] = sa[i];
	for (int i = n1; i < n; ++i) sa[i] = -1;
	int name = 0, prev = -1;
	for (int i = 0; i < n1; ++i)
	{
		int pos = sa[i];
		bool diff = false;
		for (int d = 0; d < n; ++d)
			if (prev==-1 || s[pos + d] != s[prev + d] || type[pos + d] != type[prev + d])
			{
				diff = true;
				break;
			}
			else if (d > 0 && (isLMS(pos + d) || isLMS(prev + d)))
				break;
		if (diff)
		{
			name++;
			prev = pos;
		}
		pos /= 2;
		sa[n1 + pos] = name - 1;
	}
	for (int i = n - 1, j = n - 1; i >= n1; --i)
		if (sa[i] >= 0) sa[j--] = sa[i];
	int *sa1 = sa, *s1 = sa + n - n1;
	if (name < n1) sa_is(s1, sa1, n1, bkt);
	else for (int i = 0; i < n1; ++i) sa1[s1[i]] = i;
	get_buckets(s, n, bkt, K, true);
	for (int i = 1, j = 0; i < n; ++i)
		if (isLMS(i)) s1[j++] = i;
	for (int i = 0; i < n1; ++i) sa1[i] = s1[sa1[i]];
	for (int i = n1; i < n; ++i) sa[i] = -1;
	for (int i = n1 - 1, j; i >= 0; --i)
	{
		j = sa[i]; sa[i] = -1;
		sa[--bkt[s[j]]] = j;
	}
	induce_sort(s, sa, n, type, bkt, K);
}

template<typename RAIter>
pair<vector<int>, vector<int>> suffix_array(RAIter beg, RAIter end)
{
	const int n = distance(beg, end);
	if (n < 2) return make_pair(vector<int>(n), vector<int>(n));
	vector<int> s(n + 1), sa(n + 1), rank(n);
	for (int i = 0; i < n; ++i) s[i] = (int) beg[i] + 1;
	int alpha = (n + 1) / 2;
	for (int i = 0; i < n; ++i) alpha = max(alpha, s[i]);
	if (alpha > 5000000) // adjust this value
		throw invalid_argument("big alpha!!!");
	vector<int> bkt(alpha + 1);
	sa_is(&s[0], &sa[0], n + 1, bkt);
	assert(sa[0] == n);
	sa.erase(sa.begin());
	for (int i = 0; i < n; ++i) rank[sa[i]] = i;
	return make_pair(move(sa), move(rank));
}
