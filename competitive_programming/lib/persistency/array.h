#include <vector>

using std::vector;

template <typename T>
struct Array {
    struct Node {
        Node *l = nullptr, *r = nullptr;
        int tl, tr;
        T val = -1;

        Node(int tl, int tr) : tl(tl), tr(tr) {}
        Node(Node *u) {
            *this = *u;
        }
    };

    void build(Node *u, const vector <T>& a) {
        if (u->tl == u->tr) {
            u->val = a[u->tl];
        }
        else {
            int tm = (u->tl + u->tr) / 2;

            u->l = new Node(u->tl, tm);
            u->r = new Node(tm + 1, u->tr);

            build(u->l, a);
            build(u->r, a);
        }
    }

    vector <Node*> roots;

    Array(const vector <T>& a) {
        roots.push_back(new Node(0, int(a.size()) - 1));
        build(roots.front(), a);
    }

    Node* update(Node *u, int pos, T val) {
        if (u->tl == u->tr) {
            Node *v = new Node(u);
            v->val = val;
            return v;
        }
        else {
            Node *v = new Node(u);
            if (pos <= (u->tl + u->tr) / 2) {
                v->l = update(u->l, pos, val);
            }
            else {
                v->r = update(u->r, pos, val);
            }
            return v;
        }
    }

    T get(Node *u, int pos) {
        if (u->tl == u->tr) {
            return u->val;
        }
        else {
            if (pos <= (u->tl + u->tr) / 2) {
                return get(u->l, pos);
            }
            else {
                return get(u->r, pos);
            }
        }
    }

    inline void update(int version, int pos, T val) {
        roots.push_back(update(roots[version], pos, val));
    }

    inline T get(int version, int pos) {
        return get(roots[version], pos);
    }
};


