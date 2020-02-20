template<typename H, typename T>
struct hash_table
{
	static const int n = 5000010, mod = 5000007;

	H h[n];
	T val[n];
	int f, p, c, link[n], last[mod];

	hash_table() : f(0), p(0), c(0) { memset(last, -1, sizeof last); }

	T* find(H hash)
	{
		for (f = -1, p = last[hash % mod]; p != -1; f = p, p = link[p])
			if (h[p] == hash)
				return &val[p];
		return NULL;
	}

	void set(H hash, T num)
	{
		if (find(hash) != NULL)
			val[p] = num;
		else
		{
			h[c] = hash;
			val[c] = num;
			hash %= mod;
			link[c] = last[hash];
			last[hash] = c++;
		}
	}
	
	void erase(H hash)
	{
		if (find(hash) == NULL)
			return;

		if (f == -1)
			last[hash % mod] = link[p];
		else
			link[f] = link[p];
	}
};