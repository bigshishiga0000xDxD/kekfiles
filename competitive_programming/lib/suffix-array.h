#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

const int N = 1e5;

// O(nlogn)
struct SuffixArray {
    SuffixArray() {}

    int s[N], c[N], lcp[N];

    int operator[](int i) {
        return s[i];
    }

    SuffixArray(const string& str) {
        int n = str.size();
        vector <vector <int>> cnt(max(n, 256)), cnt2(n);

        for (int i = 0; i < n; i++) {
            cnt[str[i]].push_back(i);
        }

        int ptr = 0, cls = 0;
        for (int i = 0; i < 256; i++) {
            for (int pos : cnt[i]) {
                s[ptr++] = pos;
                c[pos] = cls;
            }
            cls += (!cnt[i].empty());
        }

        vector <int> cnew(n);
        for (int pw = 1; pw <= n; pw *= 2) {
            for (int i = 0; i < n; i++) {
                cnt[i].clear();
                cnt2[i].clear();
            }

            for (int i = 0; i < n; i++) {
                cnt[c[(i + pw) % n]].push_back(i);
            }

            for (int i = 0; i < n; i++) {
                for (int j : cnt[i]) {
                    cnt2[c[j]].push_back(j);
                }
            }

            ptr = 0;
            for (int i = 0; i < n; i++) {
                for (int j : cnt2[i]) {
                    s[ptr++] = j;
                }
            }

            cls = cnew[s[0]] = 0;
            for (int i = 1; i < n; i++) {
                cls += !(c[s[i]] == c[s[i - 1]] && c[(s[i] + pw) % n] == c[(s[i - 1] + pw) % n]);
                cnew[s[i]] = cls;
            }

            for (int i = 0; i < n; i++) {
                c[i] = cnew[i];
            }
        }

        for (int i = 0, cur = 0; i < n; i++) {
            if (c[i] == n - 1) continue;
            int j = s[c[i] + 1];

            while (i + cur < n && j + cur < n && str[i + cur] == str[j + cur]) {
                cur++;
            }
            lcp[c[i]] = cur;

            cur = max(cur - 1, 0);
        }
    }
};
