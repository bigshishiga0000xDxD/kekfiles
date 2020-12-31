#include <vector>
#include <algorithm>

using std::vector;
using std::upper_bound;

typedef long long ll;
typedef long double ld;

const int INF = 2e18;

struct Hull {
    struct Line {
        ll k, b;

        ld eval(ld x) {
            return k * x + b;
        }

        ll eval(ll x) {
            return k * x + b;
        }
    };

    vector <Line> lines;
    vector <ld> x;

    ld cross(Line x, Line y) {
        return ld(y.b - x.b) / (x.k - y.k);
    }

    void add(Line line) {
        while (!lines.empty() && lines.back().eval(x.back()) > line.eval(x.back())) {
            lines.pop_back();
            x.pop_back();
        }

        if (lines.empty()) {
            x.push_back(-INF);
        }
        else {
            x.push_back(cross(lines.back(), line));
        }
        lines.push_back(line);
    }

    ll get(ll cx) {
        int ptr = upper_bound(x.begin(), x.end(), cx) - x.begin() - 1;
        return lines[ptr].eval(cx);
    }
};
