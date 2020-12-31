#include <algorithm>

using std::max;

const int N = 2e7;
const int K = 12;    // log2(N) / 2
const int logm = 21; // log2(N / K)
const int INF = 2e9;


struct Fkb {
    int a[N];

    int dp[N / K + 1][logm];
    int logs[N / K + 1];
    int p[K][1 << K];
    int msk[N];

    inline int _get(int l, int r) {
        if (l == r) {
            return a[l];
        }
        else {
            int mask = (msk[r] - msk[l]) >> (l - l / K * K + 1);
            return a[l] + p[r - l - 1][mask];
        }
    }

    int query(int l, int r) {
        int lb = l / K + 1;
        int rb = r / K - 1;

        int res = -INF;
        if (lb - rb == 2) {
            res = _get(l, r); 
        }
        else {
            if (rb >= lb) {
                int lg = logs[rb - lb + 1];
                res = max(dp[lb][lg], dp[rb - (1 << lg) + 1][lg]);
            }

            lb *= K;
            rb *= K;
            lb--;
            rb += K;

            res = max(res, _get(l, lb));
            res = max(res, _get(rb, r));
        }
        
        return res;
    }

    Fkb(int n) {
        int m = (n + K - 1) / K;
        for (int i = 0; i < m; i++) {
            dp[i][0] = -INF;
        }

        for (int i = 0; i < n; i++) {
            dp[i / K][0] = max(dp[i / K][0], a[i]);
        }

        for (int j = 1; j < logm; j++) {
            for (int i = 0; i + (1 << j) - 1 < m; i++) {
                dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }

        logs[1] = 0;
        for (int i = 2; i < N / K + 1; i++) {
            logs[i] = logs[i >> 1] + 1;
        }

        for (int len = 1; len <= K; len++) {
            for (int mask = 0; mask < (1 << len); mask++) {
                int cur = 0, best = 0;
                for (int i = 0; i < len; i++) {
                    if (mask >> i & 1) {
                        cur++;
                    }
                    else {
                        cur--;
                    }

                    if (cur > best) {
                        best = cur;
                    }
                }
                p[len - 1][mask] = best;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i % K) {
                int x = (a[i] > a[i - 1]);
                msk[i] = msk[i - 1] + (x << (i % K));         
            }
            else {
                msk[i] = 0;
            }
        }
    }
};
