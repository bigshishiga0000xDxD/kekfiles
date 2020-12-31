#include <vector>
#include <string>

using std::vector;
using std::string;
using std::min;

// odd palindromes only
vector <int> manaker(const string& s) {
    int n = s.size();
    vector <int> a(n);

    for (int i = 0, l = 0, r = 0; i < n; i++) {
        a[i] = (i > r ? 0 : min(r - i, a[2 * l - i]));

        while (i + a[i] < n && i - a[i] >= 0 && s[i + a[i]] == s[i - a[i]]) {
            a[i]++;
        }

        if (i + a[i] - 1 > r) {
            l = i, r = i + a[i] - 1;
        }
    }

    return a;
}
