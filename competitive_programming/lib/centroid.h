#include <vector>

using std::vector;

const int N = 1e5;

int n;
vector <int> g[N];

struct Centroid {
    int pr[N], s[N];
    char used[N];
    
    Centroid() {}

    void dfs_count(int u, int p = -1) {
        s[u] = 1;
        for (int v : g[u]) {
            if (!used[v] && v != p) {
                dfs_count(v, u);
                s[u] += s[v];
            }
        }
    }

    int dfs_centroid(int u, int m, int p = -1) {
        for (int v : g[u]) {
            if (!used[v] && v != p && s[v] > m / 2) {
                return dfs_centroid(v, m, u);
            }
        }
        return u;
    }

    void dfs_decomposition(int u) {
        for (int v : g[u]) {
            if (!used[v]) {
                dfs_count(v);
                int k = dfs_centroid(v, s[v]);

                used[k] = 1;
                pr[k] = u;

                dfs_decomposition(k);
            }
        }
    }

    void build(int start) {
        dfs_count(start);
        int k = dfs_centroid(start, n);
        used[k] = 1;
        pr[k] = -1;
        dfs_decomposition(k);
    }
};
