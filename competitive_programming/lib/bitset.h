#include <algorithm>
#include <string>

using std::string;

template <size_t N>
struct Bitset {
    unsigned long long a[(N + 63) / 64];

    Bitset() {
        memset(a, 0, sizeof a);
    }

    inline bool get(size_t i) const {
        return a[i / 64] >> (i % 64) & 1;
    }

    inline void set(size_t i, bool val) {
        a[i / 64] &= ~0ULL ^ (1ULL << (i % 64));
        a[i / 64] |= static_cast<unsigned long long>(val) << (i % 64);
    }

    size_t ffs() {
        for (size_t i = 0; i < (N + 63) / 64; i++) {
            if (a[i]) {
                for (size_t j = 0; ; j++) {
                    if (a[i] >> j & 1) {
                        return i * 64 + j;
                    }
                }
            }
        }
        return N;
    }

    operator string() {
        string res;
        for (size_t i = 0; i < N; i++) {
            res += '0' + get(i);
        }
        return res;
    }

    Bitset<N>& operator^=(const Bitset<N>& rhs) {
        for (size_t i = 0; i < (N + 63) / 64; i++) {
            a[i] ^= rhs.a[i];
        }
        return *this;
    }

    friend Bitset<N> operator^(Bitset<N> lhs, const Bitset<N>& rhs) {
        lhs ^= rhs;
        return lhs;
    }

    Bitset<N>& operator|=(const Bitset<N>& rhs) {
        for (size_t i = 0; i < (N + 63) / 64; i++) {
            a[i] |= rhs.a[i];
        }
        return *this;
    }

    friend Bitset<N> operator|(Bitset<N> lhs, const Bitset<N>& rhs) {
        lhs |= rhs;
        return lhs;
    }

    Bitset<N>& operator&=(const Bitset<N>& rhs) {
        for (size_t i = 0; i < (N + 63) / 64; i++) {
            a[i] &= rhs.a[i];
        }
        return *this;
    }

    friend Bitset<N> operator&(Bitset<N> lhs, const Bitset<N>& rhs) {
        lhs &= rhs;
        return lhs;
    }
};

template <size_t N>
bool operator<(const Bitset<N>& a, const Bitset<N>& b) {
    size_t i = (a ^ b).ffs();
    return (i < N ? !a.get(i) : false);
}

