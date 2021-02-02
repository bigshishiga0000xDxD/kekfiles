typedef long long ll;

template <int N, int MOD>
struct C {
    ll inv[N], fact[N], ifact[N];

    C() {
        inv[1] = 1;
        for (int i = 2; i < N; i++) {
            inv[i] = ((-(MOD / i) * inv[MOD % i]) % MOD + MOD) % MOD;
        }

        fact[0] = 1;
        for (int i = 1; i < N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        ifact[0] = 1;
        for (int i = 1; i < N; i++) {
            ifact[i] = ifact[i - 1] * inv[i] % MOD;
        }
    }

    inline ll calc(int n, int k) {
        if (k > n || k < 0) return 0;
        return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
    }
};

