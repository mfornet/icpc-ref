// longest length that the preffix ending in i is equal to suffix start in 0
vector<int> pi_function(const string &s)
{
	int n = s.length();
	vector<int> pi(n);

	for (int i = 1, k = 0; i < n; ++i)
	{
		while (k && s[i] != s[k])
			k = pi[k - 1];
		k += s[i] == s[k];
		pi[i] = k;
	}

	return pi;
}

// matchs of pattern in text
vector<int> kmp(const string &text, const string &patt)
{
	int n = text.length(), m = patt.length();
	vector<int> ans, pi = pi_function(patt);

	for (int i = 0, k = 0; i < n; ++i)
	{
		while (k && text[i] != patt[k])
			k = pi[k - 1];
		k += text[i] == patt[k];
		if (k == m)
		{
			ans.push_back(i - k + 1);
			k = pi[k - 1];
		}
	}

	return ans;
}


// minimum length l that s can be represented as a concatenation of copies l
int compression_line(const string &s)
{
	int l = s.length() - pi_function(s).back();
	return s.length() % l == 0 ? l : s.length();
}

// counting the number of occurrences of each prefix
vector<int> prefix_occurrences(const string &s)
{
	int n = s.length();
	vector<int> ans(n + 1), pi = pi_function(s);

	for (int p : pi)
		++ans[p];
	for (int i = n - 1; i; --i)
		ans[pi[i - 1]] += ans[i];

	ans.erase(ans.begin());
	return ans;
}
