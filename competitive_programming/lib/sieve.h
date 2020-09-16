#include <vector>
using namespace std;

template <typename T>
struct Sieve {
    vector <T> primes;   // primes;
    vector <T> d;        // index of smallest prime divisor
    vector <T> p;        // smallest divisor
    vector <T> y;        // greatest divisor
    vector <T> deg;      // power of smallest divisor
    vector <T> rest;     // i / p[i] ** deg[i]
    vector <T> term;     // p[i] ** deg[i]
    vector <T> phi;      // Euler's phi function
    vector <T> sigma;    // number of divisors
    vector <T> sigma1;   // sum of divisors

    Sieve(int n) {
        d = vector <T> (n + 1, -1);
        p = y = deg = rest = term = phi = sigma = sigma1 = vector <T> (n + 1);
        phi[1] = sigma[1] = 1;

        for (int i = 2; i <= n; i++) {
            if (d[i] == -1) {
                d[i] = primes.size();
                primes.push_back(i);
            }

            for (int j = 0; j <= d[i] && i * primes[j] <= n; j++) {
                d[i * primes[j]] = d[primes[j]];
            }
        }

        sigma1[1] = 1;
        for (int i = 2; i <= n; i++) {
            p[i] = primes[d[i]];
            y[i] = i / p[i];
            deg[i] = (d[y[i]] == d[i] ? deg[y[i]] + 1 : 1);
            rest[i] = (d[y[i]] == d[i] ? rest[y[i]] : y[i]);
            term[i] = i / rest[i];
            phi[i] = (term[i] - term[i] / p[i]) * phi[rest[i]];
            sigma[i] = sigma[rest[i]] * (deg[i] + 1);
            sigma1[i] = sigma1[rest[i]] * (term[i] * p[i] - 1) / (p[i] - 1);
        }
    }
};
