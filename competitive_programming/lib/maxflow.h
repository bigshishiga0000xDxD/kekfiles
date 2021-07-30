#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::min;
using std::tuple;

typedef long long ll;
template <typename T>
struct Edge {
    int v;
    T c, f;
};


template <typename T, int N, T INF>
struct MaxFlowSolver {
    int n, s, t;
    vector <Edge <T>> e;
    vector <int> g[N];

    MaxFlowSolver(int n) : n(n), s(0), t(n - 1) {}
    MaxFlowSolver(int n, int s, int t) : n(n), s(s), t(t) {}

    void add_edge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.push_back({ v, c, 0 });
        g[v].push_back(e.size());
        e.push_back({ u, 0, 0 });
    }

    vector <tuple <int, int, T, T>> result() {
        vector <tuple <int, int, T, T>> res;

        for (int u = 0; u < n; u++) {
            for (int i : g[u]) {
                if (i % 2 == 0) {
                    res.push_back({ u, e[i].v, e[i].c, e[i].f });
                }
            }
        }

        return res;
    }

    void clear() {
        for (Edge<T>& edge : e) {
            edge.f = 0;
        }
    }

    char used[N];

    T dfs_ff(int u, T x = INF) {
        used[u] = 1;
        if (u == t) return x;

        for (int i: g[u]) {
            if (!used[e[i].v] && e[i].f < e[i].c) {
                T y = dfs_ff(e[i].v, min(x, e[i].c - e[i].f));
                if (!y) continue;

                x = min(x, y);

                e[i].f += x;
                e[i ^ 1].f -= x;
                return x;
            }
        }

        return 0;
    }

    ll FordFulkerson() {
        ll ans = 0;
        memset(used, 0, sizeof used);

        while (T p = dfs_ff(s)) {
            ans += p;
            memset(used, 0, sizeof used);
        }
        return ans;
    }

    int d[N], ptr[N];

    bool bfs(T delta = 1) {
        fill(d, d + N, 1e9);
        d[s] = 0;

        queue <int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i : g[u]) {
                int v = e[i].v;
                if (e[i].f + delta <= e[i].c && d[u] + 1 < d[v]) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
       }

        return d[t] < 1e9;
    }

    T dfs_dinic(int u, T x = INF) {
        if (u == t) return x;

        for (; ptr[u] < int(g[u].size()); ptr[u]++) {
            int i = g[u][ptr[u]], v = e[i].v;
            if (e[i].f < e[i].c && d[u] + 1 == d[v]) {
                T y = dfs_dinic(v, min(x, e[i].c - e[i].f));
                if (!y) continue;

                x = min(x, y);

                e[i].f += x;
                e[i ^ 1].f -= x;
                return x;
            }
        }

        return 0;
    }

    ll Dinic() {
        ll ans = 0;
        while (bfs()) {
           memset(ptr, 0, sizeof ptr);
            while (T x = dfs_dinic(s)) {
                ans += x;
            }
        }
        return ans;
    }

    bool dfs_ds(int u, T delta) {
        if (u == t) return true;

        for (; ptr[u] < int(g[u].size()); ptr[u]++) {
            int i = g[u][ptr[u]], v = e[i].v;
            if (e[i].f + delta <= e[i].c && d[u] + 1 == d[v]) {
                if (!dfs_ds(v, delta)) continue;

                e[i].f += delta;
                e[i ^ 1].f -= delta;
                return true;
            }
        }

        return false;
    }

    ll DinicScaling(int lgc) {
        ll ans = 0;
        for (T delta = (T(1) << lgc); delta; delta >>= 1) {
            while (bfs(delta)) {
                memset(ptr, 0, sizeof ptr);
                while (dfs_ds(s, delta)) {
                    ans += delta;
                }
            }
        }
        return ans;
    }
}; 

