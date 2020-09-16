typedef long long ll;

template <int N, int MOD>
struct C {
	ll fact[N];

	C() {
		fact[0] = 1;
		for (int i = 1; i < N; i++) {
			fact[i] = (fact[i - 1] * i) % MOD;
		}
	}

	ll modpow(ll b, ll e) {
		if (e == 0) {
			return 1;
		}
		if (e % 2) {
			return (b * modpow(b, e - 1)) % MOD;
		}
		else {
			return modpow((b * b) % MOD, e / 2);
		}
	}
	
	inline ll inv(ll x) {
		return modpow(x, MOD - 2);
	}
	
    ll calc(ll n, ll k) {
        if (k > n) {
            return 0;
        }
        else {
            return ((fact[n] * inv(fact[k])) % MOD) * inv(fact[n - k]) % MOD;
        }
    }
};

