#include <vector>

using std::vector;
using std::swap;

const int N = 1e5;

vector <int> g[N];

// [tin[u]; tin[next[u]] - ascending heavy path
// [tin[u]; tout[u]) - subtree
struct Hld {
    int s[N], tin[N], tout[N], next[N], t = 0;

    void dfs_size(int u, int p = -1) {
        if (g[u].front() == p) {
            swap(g[u].front(), g[u].back());
        } 

        s[u] = 1;
        for (int& v : g[u]) {
            if (v != p) {
                dfs_size(v, u);
                s[u] += s[v];

                if (s[v] > s[g[u].front()]) {
                    swap(v, g[u].front());
                }
            }
        }
    }

    void dfs_hld(int u, int p = -1) {
        tin[u] = t++;

        for (int v : g[u]) {
            if (v != p) {
                next[v] = (v == g[u].front() ? next[u] : v);
                dfs_hld(v, u);
            }
        }
        tout[u] = t;
    }

    void build(int root) {
        dfs_size(root);
        next[root] = root;
        dfs_hld(root);
    }
};
