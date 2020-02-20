// the list of woman preference in descending order and the attractiveness for each man
vector<int> stable_marriage_problem(vector<vector<int>> &man, vector<vector<int>> &wom)
{
	const int n = man.size();
	vector<int> husb(wom.size(), -1), wife(n, -1), p(n, 0);

	for (int i = 0, m = 0, w, old; i < n; m = ++i)
		for (; m != -1; old = husb[w], wife[husb[w] = m] = w, m = old)
			do
			{
				w = man[m][p[m]++];
			} while (husb[w] != -1 && wom[w][m] < wom[w][husb[w]]);

	return wife;
}