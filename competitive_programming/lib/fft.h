#include <complex>
#include <vector>

using std::complex;
using std::vector;

template <typename Base = int>
class PolynomMultiplierCommon {
    public: static void shrink(vector <Base>& a) {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    template <typename T>
    vector <Base> pow(vector <Base> a, T e) {
        vector <Base> res = { 1 };
        while (e) {
            if (e % 2) {
                res = multiply(res, a);
            }
            a = multiply(a, a);
            e /= 2;
        }
        return res;
    }
};

template <typename Base = int, typename Prec = double>
class PolynomMultiplier : public PolynomMultiplierCommon<Base> {
    const Prec pi = acos(-1);
    typedef complex<Prec> Complex;

    template <typename T>
    void fft(T *a, Complex *ans, Complex wn, size_t n, size_t step = 1) {
        if (n == 1) {
            *ans = *a;
        } else {
            n >>= 1;
            fft(a, ans, wn * wn, n, step << 1);
            fft(a + step, ans + n, wn * wn, n, step << 1);

            Complex w = 1;
            for (size_t i = 0; i < n; i++) {
                auto x = w * ans[i + n];
                ans[i + n] = ans[i] - x;
                ans[i] += x;

                w *= wn;
            }
        }
    }

    template <typename T>
    void fft(vector <T>& a, vector <Complex>& ans, Complex wn) {
        fft(a.data(), ans.data(), wn, a.size(), 1);
    }

    vector <Base> interpolate(vector <Complex>& a, vector <Complex>& tmp) {
        size_t n = a.size();
        fft(a, tmp, polar(1.0, -2 * pi / n));

        vector <Base> res(n);
        for (size_t i = 0; i < n; i++) {
            res[i] = round(real(tmp[i]) / n);
        }
        PolynomMultiplierCommon<Base>::shrink(res);

        return res;
    }

    public: vector <Base> multiply(vector <Base> a, vector <Base> b) {
        size_t n = 1;
        while (n < max(a.size(), b.size())) n <<= 1;
        n <<= 1;

        a.resize(n), b.resize(n);

        Complex wn(polar(1.0, 2 * pi / n));
        vector <Complex> fa(n), fb(n);

        fft(a, fa, wn);
        fft(b, fb, wn);

        vector <Base> res;
        for (size_t i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }

        return interpolate(fa, fb);
    }
};


template <typename Base = int>
class ModPolynomMultiplier : public PolynomMultiplierCommon<Base> {
    static const int MOD = 998244353;
    Base pws[24];
    Base inv[24];

    public: constexpr ModPolynomMultiplier() {
        pws[23] = 31;
        inv[23] = 998244234;

        for (int i = 22; i >= 0; i--) {
            pws[i] = 1LL * pws[i + 1] * pws[i + 1] % MOD;
            inv[i] = inv[i + 1] * 2 % MOD;
        }
    }

    private: void fft(Base *a, Base *ans, Base wn, size_t n, size_t step = 1) {
        if (n == 1) {
            *ans = *a;
        } else {
            n >>= 1;
            fft(a, ans, 1LL * wn * wn % MOD, n, step << 1);
            fft(a + step, ans + n, 1LL * wn * wn % MOD, n, step << 1);

            Base w = 1;
            for (size_t i = 0; i < n; i++) {
                Base x = 1LL * w * ans[i + n] % MOD;
                ans[i + n] = ans[i] - x;
                ans[i] += x;

                if (ans[i] >= MOD)  ans[i] -= MOD;
                if (ans[i + n] < 0) ans[i + n] += MOD;

                w = 1LL * w * wn % MOD;
            }
        }
    }

    void fft(vector <Base>& a, vector <Base>& ans, Base wn) {
        fft(a.data(), ans.data(), wn, a.size(), 1);
    }

    vector <Base> interpolate(vector <Base>& a, vector <Base>& tmp, Base wn, Base invn) {
        size_t n = a.size();
        fft(a, tmp, wn);
        reverse(tmp.begin() + 1, tmp.end());

        vector <Base> res(n);
        for (size_t i = 0; i < n; i++) {
            res[i] = 1LL * tmp[i] * invn % MOD;
        }
        PolynomMultiplierCommon<Base>::shrink(res);

        return res;
    }

    public: vector <Base> multiply(vector <Base> a, vector <Base> b) {
        size_t n = 1, k = 0;
        while (n < max(a.size(), b.size())) n <<= 1, k++;
        n <<= 1, k++;

        a.resize(n), b.resize(n);

        vector <Base> fa(n), fb(n);
        fft(a, fa, pws[k]);
        fft(b, fb, pws[k]);

        vector <Base> res;
        for (size_t i = 0; i < n; i++) {
            fa[i] = 1LL * fa[i] * fb[i] % MOD;
        }

        return interpolate(fa, fb, pws[k], inv[k]);
    }
};

