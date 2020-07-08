#include <iostream>
#include <chrono>
#include <random>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rng_on(int l, int r) {
    return rng() % (r - l + 1) + l;
}

signed main() {
    //freopen("input.txt", "w", stdout);
    
    
    
    return 0;
}