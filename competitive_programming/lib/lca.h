#include <vector>

using std::vector;
using std::pair;
using std::swap;

const int N = 1e5;
const int logn = 18; // ceil(log2(2N))

vector <int> g[N];

struct Tree {
    int d[N], t[N], log[2 * N];
    vector <int> order, depth;
    pair <int, int> dp[2 * N][logn];

    void dfs(int u, int p = -1) {
        order.push_back(u);
        depth.push_back(d[u]);

        for (int v : g[u]) {
            if (v != p) {
                d[v] = d[u] + 1;
                dfs(v, u);
                order.push_back(u);
                depth.push_back(d[u]);
            }
        }
    }

    Tree() {}

    void build(int start) {
        dfs(start);

        int m = order.size();
        for (int i = 0; i < m; i++) {
            t[order[i]] = i;
        }

        log[1] = 0;
        for (int i = 2; i < 2 * N; i++) {
            log[i] = log[i >> 1] + 1;
        }

        for (int i = 0; i < m; i++) {
            dp[i][0] = { depth[i], i };
        }

        for (int j = 1; j < logn; j++) {
            for (int i = 0; i < m; i++) {
                if (i + (1 << j) < m) {
                    dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }

    inline int lca(int u, int v) {
        u = t[u], v = t[v];
        if (u > v) swap(u, v);
        int lg = log[v - u + 1];
        return order[min(dp[u][lg], dp[v - (1 << lg) + 1][lg]).second];
    }

    inline int distance(int u, int v) {
        return d[u] + d[v] - 2 * d[lca(u, v)];
    }
};
