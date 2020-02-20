/*
	Tested: ZOJ 3885
*/

template<typename T, typename C = T>
struct min_cost_flow
{
	struct edge
	{
		int src, dst;
		T cap, flow;
		C cost;
		int rev;
	};

	int n;
	vector<vector<edge>> adj;

	min_cost_flow(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst, T cap, C cost)
	{
		adj[src].push_back({ src, dst, cap, 0, cost, (int) adj[dst].size() });
		if (src == dst)
			adj[src].back().rev++;
		adj[dst].push_back({ dst, src, 0, 0, -cost, (int) adj[src].size() - 1 });
	}

	const C oo = numeric_limits<C>::max();

	vector<C> dist, pot;
	vector<edge*> prev;

	bool dijkstra(int s, int t)
	{
		dist.assign(n, oo);
		prev.assign(n, nullptr);
		dist[s] = 0;

		using pci = pair<C, int>;
		priority_queue<pci, vector<pci>, greater<pci>> pq;
		pq.push({ 0, s });

		while (!pq.empty())
		{
			C d; int u;
			tie(d, u) = pq.top();
			pq.pop();

			if (d != dist[u])
				continue;

			for (auto &e : adj[u])
				if (e.flow < e.cap
						&& dist[e.dst] > dist[u] + e.cost + pot[u] - pot[e.dst])
				{
					dist[e.dst] = dist[u] + e.cost + pot[u] - pot[e.dst];
					prev[e.dst] = &e;
					pq.push({ dist[e.dst], e.dst });
				}
		}

		return dist[t] < oo;
	}

	pair<T, C> max_flow(int s, int t)
	{
		T flow = 0;
		C cost = 0;

		pot.assign(n, 0);
		while (dijkstra(s, t))
		{
			for (int u = 0; u < n; ++u)
				if (dist[u] < oo)
					pot[u] += dist[u];

			T delta = numeric_limits<T>::max();
			for (edge *e = prev[t]; e != nullptr; e = prev[e->src])
				delta = min(delta, e->cap - e->flow);

			flow += delta;
			for (edge *e = prev[t]; e != nullptr; e = prev[e->src])
			{
				e->flow += delta;
				adj[e->dst][e->rev].flow -= delta;
				cost += delta * e->cost;
			}
		}

		return {flow, cost};
	}
};
