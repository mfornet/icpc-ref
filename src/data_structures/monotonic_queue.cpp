/*
	Sliding Maximum

	Notes: remove(make sure call it before max) erase all values with position <= k

	Complexity: O(1) amortized
*/
template<typename T>
struct monotonic_queue
{
	deque<pair<int, T>> deq;

	void add(int k, T v)
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

	T max()
	{
		return deq.front().second;
	}
};