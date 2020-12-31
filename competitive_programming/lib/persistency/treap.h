#include <random>

using std::mt19937;
using std::pair;

mt19937 rng(228);

template <typename T>
struct Treap {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;

        int cnt = 1;
        T val;

        Node(T val) : val(val) {}

        Node(Node *v) {
            *this = *v;
        }
    };

    inline int get(Node *u) {
        return (u ? u->cnt : 0);
    }

    void update(Node *u) {
        u->cnt = get(u->l) + get(u->r) + 1;
    }

    Treap() {}
    Treap(Node *u) : root(u) {}

    Node *root = nullptr;

    pair <Node*, Node*> split(Node *u, int key) {
        if (!u) {
            return { nullptr, nullptr };
        }

        if (key <= get(u->l)) {
            auto [left, right] = split(u->l, key);
            u->l = right;
            update(u);

            return { left, u };
        }
        else {
            auto [left, right] = split(u->r, key - get(u->l) - 1);
            u->r = left;
            update(u);

            return { u, right };
        }
    }

    pair <Node*, Node*> persistent_split(Node *u, int key) {
        if (!u) {
            return { nullptr, nullptr };
        }

        auto w = new Node(u);
        if (key <= get(u->l)) {
            auto [left, right] = persistent_split(u->l, key);
            w->l = right;
            update(w);

            return { left, w };
        }
        else {
            auto [left, right] = persistent_split(u->r, key - get(u->l) - 1);
            w->r = left;
            update(w);

            return { w, right };
        }
    }

    Node* merge(Node *u, Node *v) {
        if (!u) return v;
        if (!v) return u;

        if (rng() % (get(u) + get(v)) < get(u)) {
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

    Node* persistent_merge(Node *u, Node *v) {
        if (!u) return v;
        if (!v) return u;

        auto uc = new Node(u), vc = new Node(v);
        if (rng() % (get(u) + get(v)) < get(u)) {
            uc->r = persistent_merge(u->r, v);
            update(uc);

            return uc;
        }
        else {
            vc->l = persistent_merge(u, v->l);
            update(vc);

            return vc;
        }
    }
};


