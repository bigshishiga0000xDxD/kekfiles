#include <complex>
#include <vector>

using std::complex;
using std::vector;


template <typename Base>
class PolynomMultiplierCommon {
    public: static void shrink_zeros(vector <Base>& a) {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    static void shrink_extra(vector <Base>& a, size_t len) {
        if (a.size() > len) a.resize(len);
    }

    static size_t get_log(size_t x) {
        size_t k = 0;
        while ((static_cast<size_t>(1) << k) < x) k++;
        return k;
    }

    static void shift_right(vector <Base>& a, size_t k) {
        reverse(a.begin(), a.end());
        a.resize(a.size() + k);
        reverse(a.begin(), a.end());
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
    const Prec pi = acos(static_cast<Prec>(-1));
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

    vector <Base> interpolate(vector <Complex> a, vector <Complex> tmp) {
        size_t n = a.size();
        fft(a, tmp, polar(static_cast<Prec>(1.0), -2 * pi / n));

        vector <Base> res(n);
        for (size_t i = 0; i < n; i++) {
            res[i] = round(real(tmp[i]) / n);
        }

        return res;
    }

     public: vector <Base> multiply(vector <Base>& a, vector <Base>& b) {
        size_t len = a.size() + b.size() - 1;
        size_t k = PolynomMultiplierCommon<Base>::get_log(max(a.size(), b.size())) + 1;
        size_t n = (1 << k);

        Complex wn(polar(static_cast<Prec>(1.0), 2 * pi / n));
        auto fa = get_dft(a, n, wn);
        auto fb = get_dft(b, n, wn);

        return get_result(move(fa), move(fb), len);
   }

    vector <Complex> get_dft(vector <Base> a, size_t n, Complex wn) {
        a.resize(n);
        vector <Complex> res(n);
        fft(a, res, wn);

        return res;
    }

    vector <Base> get_result(vector <Complex> dft1, vector <Complex> dft2, size_t len) {
        size_t n = dft1.size();

        for (size_t i = 0; i < n; i++) {
            dft1[i] *= dft2[i];
        }

        auto res = interpolate(dft1, dft2);
        PolynomMultiplierCommon<Base>::shrink_extra(res, len);
        return res;
    }
};


template <typename Base = int>
class ModPolynomMultiplier : public PolynomMultiplierCommon<Base> {
    static const int MOD = 998244353;
    static const int PW2 = 23;
    static const int G = 31;          // G ^ (2 ^ PW2) mod MOD = 1; G ^ k mod MOD are distinct, k < 2 ^ PW2
    static const int INV = 998244234; // (2 ^ PW2) ^ (-1) mod MOD

    Base pws[PW2 + 1];
    Base inv[PW2 + 1];

    public: constexpr ModPolynomMultiplier() {
        pws[PW2] = G;
        inv[PW2] = INV;

        for (int i = PW2 - 1; i >= 0; i--) {
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

    void interpolate(vector <Base>& a, vector <Base>& res, Base wn, Base invn) {
        size_t n = a.size();
        fft(a, res, wn);
        reverse(res.begin() + 1, res.end());

        for (size_t i = 0; i < n; i++) {
            res[i] = 1LL * res[i] * invn % MOD;
        }
    }

    public: vector <Base> multiply(vector <Base>& a, vector <Base>& b) {
        size_t len = a.size() + b.size() - 1;
        size_t k = get_log(max(a.size(), b.size())) + 1;

        auto fa = get_dft(a, k);
        auto fb = get_dft(b, k);

        return get_result(move(fa), move(fb), k, len);
   }

    vector <Base> get_dft(vector <Base> a, size_t k) {
        size_t n = (1 << k);

        a.resize(n);
        vector <Base> res(n);
        fft(a, res, pws[k]);

        return res;
    }

    vector <Base> get_result(vector <Base> dft1, vector <Base> dft2, size_t k, size_t len) {
        size_t n = (1 << k);

        for (size_t i = 0; i < n; i++) {
            dft1[i] = 1LL * dft1[i] * dft2[i] % MOD;
        }

        interpolate(dft1, dft2, pws[k], inv[k]);
        PolynomMultiplierCommon<Base>::shrink_extra(dft2, len);
        return dft2;
    }
}; 
