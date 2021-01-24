#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;

const int N = 1e5 + 10;

struct Sat {
    int n;
    vector <int> g[2 * N], t[2 * N];

    void clear(int _n) {
        n = _n;
        for (int i = 0; i < 2 * n; i++) {
            g[i].clear();
            t[i].clear();
            used[i] = comp[i] = 0;
        }
        order.clear();
    }

    inline int get(int u, int i) {
        return (i ? u + n : u);
    }

    void add(int u, int v, int i, int j) {
        g[get(u, i ^ 1)].push_back(get(v, j));
        g[get(v, j ^ 1)].push_back(get(u, i));
        t[get(v, j)].push_back(get(u, i ^ 1));
        t[get(u, i)].push_back(get(v, j ^ 1));
    }

    int comp[2 * N];
    char used[2 * N];
    vector <int> order;

    void dfs_top(int u) {
        used[u] = 1;

        for (int v : g[u]) {
            if (!used[v]) {
                dfs_top(v);
            }
        }

        order.push_back(u);
    }

    void dfs_cond(int u, int c) {
        comp[u] = c;

        for (int v : t[u]) {
            if (!comp[v]) {
               dfs_cond(v, c);
            }
        }
    }

    vector <int> solve() {
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i]) {
                dfs_top(i);
            }
        }

        reverse(order.begin(), order.end());
        int cnt = 1;

        for (int u : order) {
            if (!comp[u]) {
                dfs_cond(u, cnt++);
            }
        }

        vector <int> ans(n);
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) {
                return { };
            }
            ans[i] = (comp[i] < comp[i + n]);
        }

        return ans;
    }
};

