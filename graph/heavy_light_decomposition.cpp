struct heavy_light_decomposition
{
    int n;
    vector<vector<int>> G;
    vector<int> parent, depth, size, head, position;
    fenwick<int> abi;
    heavy_light_decomposition(int n) :n(n), G(n), parent(n, -1), depth(n), size(n), head(n), position(n), abi(n) {}

    void add_edge(int u, int v)
    {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void rootify(int r = 0)
    {
        vector<int> heavy(n, -1), Q(1, r);

        for (int i = 0, u; i < n; ++i)
        {
            size[u = Q[i]] = 1;
            for (auto v : G[u])
                if (parent[u] != v)
                    Q.push_back(v), parent[v] = u, depth[v] = depth[u] + 1;
        }

        for (int i = n - 1, u; i >= 0; --i)
        {
            u = Q[i];
            for (auto v : G[u])
                if (parent[u] != v)
                {
                    size[u] += size[v];
                    if (heavy[u] == -1 || size[v] > size[heavy[u]])
                        heavy[u] = v;
                }
        }

        for (int u = 0, pos = 0; u < n; ++u)
            if (u == r || heavy[parent[u]] != u)
                for (int v = u; v != -1; v = heavy[v])
                    head[v] = u, position[v] = ++pos;
    }

    int lca(int u, int v)
    {
        while (head[u] != head[v])
        {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            u = parent[head[u]];
        }
        return (depth[u] < depth[v] ? u : v);
    }

    int query_up(int u, int v)
    {
        int ans = 0;
        while (head[u] != head[v])
        {
            ans += abi.query(position[u]) - abi.query(position[head[u]] - 1);
            u = parent[head[u]];
        }
        return (ans + abi.query(position[u]) - abi.query(position[v] - 1));
    }

    int query(int u, int v)
    {
        int L = lca(u, v);
        return query_up(u, L) + query_up(v, L) - query_up(L, L);
    }

    void update(int u, int c)
    {
        abi.update(position[u], c - (abi.query(position[u]) - abi.query(position[u] - 1)));
    }
};