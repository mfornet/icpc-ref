/*
	Compute for a string S the suffix array order, rank and lcp of every suffix starting in (0, 1, ..., |S|)
	
	Notes: The suffix starting in |S| is always the lowest and have lcp 0 with the next suffix.
			lcp[i] is the longest common prefix between the suffix in sa[i] and sa[i-1]
	
	Complexity: O(|S|)
*/

struct suffix_array
{
	int n;
	vector<int> sa, lcp, rank;

	suffix_array(const string &s) : n(s.length() + 1), sa(n), lcp(n), rank(n)
	{
		vector<int> top(max(256, n));
		for (int i = 0; i < n; ++i)
			top[rank[i] = s[i] & 0xff]++;

		partial_sum(top.begin(), top.end(), top.begin());
		for (int i = 0; i < n; ++i)
			sa[--top[rank[i]]] = i;

		vector<int> tmp(n);
		for (int len = 1, j; len < n; len <<= 1)
		{
			for (int i = 0; i < n; ++i)
			{
				j = sa[i] - len;
				if (j < 0) j += n;
				tmp[top[rank[j]]++] = j;
			}

			sa[tmp[top[0] = 0]] = j = 0;
			for (int i = 1, j = 0; i < n; ++i)
			{
				if (rank[tmp[i]] != rank[tmp[i - 1]]
						|| rank[tmp[i] + len] != rank[tmp[i - 1] + len])
					top[++j] = i;
				sa[tmp[i]] = j;
			}

			copy(sa.begin(), sa.end(), rank.begin());
			copy(tmp.begin(), tmp.end(), sa.begin());
			if (j >= n - 1) break;
		}

		int i, j, k;
		for (j = rank[lcp[i = k = 0] = 0]; i < n - 1; ++i, ++k)
		{
			while (k >= 0 && s[i] != s[sa[j - 1] + k])
				lcp[j] = k--, j = rank[sa[j] + 1];
		}
	}
};
