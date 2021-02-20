#include <vector>

using std::vector;
using std::swap;

typedef long long ll;

const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD;

struct Matrix {
    vector <vector <ll>> a;
    int size;
 
    Matrix(int x) {
        size = x;
        a.resize(x);
        for (auto& v : a) {
            v.resize(x);
        }
    }
 
    vector<ll>& operator[](int i) {
        return a[i];
    }

    void transporise() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i; j++) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
}; 
 

Matrix operator*(Matrix lhs, Matrix rhs) {
    int n = lhs.size;
    Matrix res(n);
 
    rhs.transporise();
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += lhs[i][k] * rhs[j][k];
                if (res[i][j] >= MOD2) {
                    res[i][j] -= MOD2;
                }
            }
            res[i][j] %= MOD;
        }
    }
 
    return res;
}
 
 
Matrix squared(Matrix m) {
    int n = m.size;
    Matrix res(n);
 
    auto t = m;
    t.transporise();
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += m[i][k] * t[j][k];
                if (res[i][j] >= MOD2) {
                    res[i][j] -= MOD2;
                }
            }
            res[i][j] %= MOD;
        }
    }
 
    return res;
}
 
Matrix binpow(Matrix m, ll k) {
    if (k == 1) {
        return m;
    }
    if (k % 2) {
        return m * binpow(m, k - 1);
    }
    else {
        return squared(binpow(m, k / 2));
    }
}
