#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

const int N = 1e5 + 10;
const int M = 3200; // N^(2/3)

struct Update {
    int pos;  // position of update
    int prev; // old value
    int next; // new value
};

struct Query {
    int t; // number of updates before query
    int l; // left bound
    int r; // right bound
    int i; // query's id
};

vector <Query> queries;

struct Set {
    // add element x to set
    inline void add(int x) {}

    // erase element x from set
    inline void erase(int x) {}

    // get current result
    inline int get() {}
} set;

vector <int> solve(vector <int> a, vector <Update> u, vector <Query> queries) {
    sort(queries.begin(), queries.end(), [] (auto x, auto y) {
        return make_tuple(x.t / M, x.l / M, x.r) < make_tuple(y.t / M, y.l / M, y.r);
    });

    vector <int> ans;

    int l = 0, r = -1, t = 0;
    for (auto query : queries) {
        if (query.r >= r) {
            while (r < query.r) {
                set.add(a[++r]);
            }
            while (l > query.l) {
                set.add(a[--l]);
            }
            while (l < query.l) {
                set.erase(a[l++]);
            }
        }
        else {
            while (l > query.l) {
                set.add(a[--l]);
            }
            while (l < query.l) {
                set.erase(a[l++]);
            }
            while (r > query.r) {
                set.erase(a[r--]);
            }
        }

        while (t < query.t) {
            int pos = u[t].pos;
            if (pos >= l && pos <= r) {
                set.erase(a[pos]);
                set.add(u[t].next);
            }
            a[pos] = u[t].next;
            t++;
        }
        while (t > query.t) {
            t--;
            int pos = u[t].pos;
            if (pos >= l && pos <= r) {
                set.erase(a[pos]);
                set.add(u[t].prev);
            }
            a[pos] = u[t].prev;
        }

        ans[query.i] = set.get();
    }

    return ans;
};
