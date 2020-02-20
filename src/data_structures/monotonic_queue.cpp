struct monotonic_queue
{
	deque<pair<int, ll>> deq;

	void add(int k, ll v)
	{
		while (!deq.empty() && deq.back().second <= v)
			deq.pop_back();
		deq.push_back({k, v});
	}

	void remove(int k)
	{
		while (!deq.empty() && deq.front().first <= k)
			deq.pop_front();
	}

	ll max()
	{
		return deq.front().second;
	}
};