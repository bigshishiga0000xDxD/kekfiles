#include <vector>

using std::vector;

// sum of subsets
vector <int> sos(const vector <int>& a) {
    int n = a.size();
    vector <int> b = a;

    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!(mask >> i & 1)) {
                b[mask | (1 << i)] += b[mask];
            }
        }
    }

    return b;
}
