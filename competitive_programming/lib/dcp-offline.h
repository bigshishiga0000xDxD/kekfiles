#include <tuple>
#include <vector>
#include <utility>
#include <map>

using std::tuple;
using std::vector;
using std::swap;
using std::pair;
using std::min;
using std::max;
using std::map;

// O(qlog^2(q) + n) time
// O(qlogq)         memory

const int N = 1e5 + 10;

struct Query {
    char type;
    int u, v;
};

struct Dsu {
    int p[N], s[N], comp;
    vector <tuple <int, int, int, int, int>> updates;

    void init(int n) {
        comp = n;
        for (int i = 0; i < n; i++) {
            p[i] = i, s[i] = 1;
        }
    }

    int find(int u) {
        while (p[u] != u) u = p[u];
        return u;
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (s[u] > s[v]) swap(u, v);

        updates.push_back({ u, v, p[u], s[v], comp });

        if (u != v) {
            p[u] = v;
            s[v] += s[u];
            comp--;
        }
    }

    void revert() {
        auto [u, v, pu, sv, _comp] = updates.back();
        updates.pop_back();

        p[u] = pu;
        s[v] = sv;
        comp = _comp;
    }
} dsu;

struct Tree {
    vector <pair <int, int>> t[4 * N];
    int n;

    void add(int v, int tl, int tr, int l, int r, pair<int, int> p) {
        if (l > r) return;
        if (tl == l && tr == r) {
            t[v].push_back(p);
        }
        else {
            int tm = (tl + tr) / 2;

            add(2 * v, tl, tm, l, min(tm, r), p);
            add(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, p);
        }
    }

    void add(int l, int r, pair<int, int> p) {
        add(1, 0, n - 1, l, r, p);
    }

    void solve(int v, int l, int r, vector <int>& ans) {
        for (auto [u, v] : t[v]) {
            dsu.join(u, v);
        }

        if (l == r) {
            // do dsu queries here
            ans[l] = dsu.comp;    
        }
        else {
            int m = (l + r) / 2;

            solve(2 * v, l, m, ans);
            solve(2 * v + 1, m + 1, r, ans);
        }

        for (int i = 0; i < int(t[v].size()); i++) {
            dsu.revert();
        }
    }

    vector <int> solve() {
        if (n) {
            vector <int> ans(n);
            solve(1, 0, n - 1, ans);
            return ans;
        }
        else {
            return {};
        }
    }
} tree;

vector <int> solve(int n, int q, vector <Query> queries) {
    for (int i = 0; i < q; i++) {
        if (queries[i].type != '?') {
            swap(queries[i].u, queries[i].v);
        }
    }

    dsu.init(n);

    vector <int> qm;
    for (int i = 0; i < q; i++) {
        if (queries[i].type == '?') {
            qm.push_back(i);
        }
    }

    tree.n = qm.size();

    map <pair <int, int>, int> mp;
    for (int i = 0; i < q; i++) {
        pair <int, int> p = { queries[i].u, queries[i].v };
        if (queries[i].type == '+') {
            mp[p] = i;
        }
        if (queries[i].type == '-') {
            int l = lower_bound(qm.begin(), qm.end(), mp[p]) - qm.begin();
            int r = lower_bound(qm.begin(), qm.end(), i) - qm.begin() - 1;
            tree.add(l, r, p);
            mp.erase(p);
        }
    }

    for (auto [p, i] : mp) {
        int l = lower_bound(qm.begin(), qm.end(), i) - qm.begin();
        tree.add(l, tree.n - 1, p);
    }

    return tree.solve();
}

