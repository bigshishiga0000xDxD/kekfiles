#include <random>

using std::mt19937;
using std::pair;

mt19937 rng(228);

template <typename T>
struct Treap {
    struct Node {
        T val;
        int pr, cnt = 1;
        Node *l = nullptr, *r = nullptr;

        Node() {}
        Node(T val) : val(val), pr(rng()) {}
    };

    inline int get(Node* u) {
        return (u ? u->cnt : 0);
    }

    inline void update(Node* u) {
        u->cnt = get(u->l) + get(u->r) + 1;
    }

    Node* root = nullptr;

    pair <Node*, Node*> split(Node* u, int k) {
        if (!u) {
            return { nullptr, nullptr };
        }
        else {
            if (k <= get(u->l)) {
                auto [left, right] = split(u->l, k);
                u->l = right;

                update(u);
                return { left, u };      
            }
            else {
                auto [left, right] = split(u->r, k - get(u->l) - 1);
                u->r = left;

                update(u);
                return { u, right };
            }
        }
    }

    Node* merge(Node* u, Node* v) {
        if (!u) {
            return v;
        }
        if (!v) {
            return u;
        }
        if (u->pr < v->pr) {
            u->r = merge(u->r, v);

            update(u);
            return u;
        }
        else {
            v->l = merge(u, v->l);

            update(v);
            return v;
        }
    }
};
