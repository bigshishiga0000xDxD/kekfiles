#include <iostream>
#include <chrono>
#include <random>
#include <set>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rng_on(int l, int r) {
    return rng() % (r - l + 1) + l;
}

signed main() {
    //freopen("input.txt", "w", stdout);

    int n;
    n = rng_on(1, 10);
    cout << n << "\n";

    set <int> s, t;
    for (int i = 0; i < n; i++) {
        int type = rng_on(0, 1);
        bool add = rng_on(0, 1);

        if (type == 0) {
            if (add) {
                int x = rng_on(1, 10);
                while (s.count(x)) {
                    x = rng_on(1, 10);
                }
                s.insert(x);
                cout << "0 " << x << "\n";
            }
            else {
                int x = rng_on(1, 10);
                while (!s.count(x)) {
                    x = rng_on(1, 10);
                }
                s.erase(x);
                cout << "0 " << -x << "\n";
            }
        }
        else {
            if (add) {
                int x = rng_on(1, 10);
                while (t.count(x)) {
                    x = rng_on(1, 10);
                }
                t.insert(x);
                cout << "0 " << x << "\n";
            }
            else {
                int x = rng_on(1, 10);
                while (!t.count(x)) {
                    x = rng_on(1, 10);
                }
                t.erase(x);
                cout << "0 " << -x << "\n";
            } 
        }
    }
   
    return 0;
}
