template<typename T>
struct fenwick
{
    int n;
    vector<T> f;
    fenwick(int n) : n(n), f(n + 1) {}

    T query(int p)
    {
        T ret = 0;
        for (++p; p > 0; p -= p & -p)
            ret += f[p];
        return ret;
    }

    void update(int p, T x)
    {
        for (++p; p <= n; p += p & -p)
            f[p] += x;
    }
};
