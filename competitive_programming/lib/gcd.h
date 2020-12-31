#include <utility>

using std::pair;

pair <int, int> gcd(int a, int b) {
    if (b == 0) {
        return { 1, 0 };
    }
    auto [xp, yp] = gcd(b, a % b);

    int x = yp;
    int y = xp - (a / b) * yp;

    return { x, y };
}
