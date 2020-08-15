template <typename T, ll N>
struct Tree {
    struct Node {
        pair <T, T> val;
        T tl, tr, pos;
        Node *l, *r;

        Node(T tl, T tr) : val(make_pair(0, 0)), tl(tl), tr(tr), l(nullptr), r(nullptr) {}
    };

    Node* root = new Node(1, N);


    pair <T, T> get(Node* u) {
        return (u ? u->val : make_pair(0, 0));
    }

    void update(Node* u) {
        u->val = max(get(u->l), get(u->r));
    }

    void update(Node *u, T pos, T val) {
        if (u->tl == u->tr) {
            u->val = { val, pos };
        }
        else {
            T tm = (u->tl + u->tr) / 2;

            if (pos <= tm) {
                if (!u->l) {
                    u->l = new Node(u->tl, tm);
                }
                update(u->l, pos, val);
            }
            else {
                if (!u->r) {
                    u->r = new Node(tm + 1, u->tr);
                }
                update(u->r, pos, val);
            }
            update(u);
        }
    }

    inline void update(T pos, T val) {
        update(root, pos, val);
    }

    pair <T, T> query(Node *u, T l, T r) {
        if (l > r || !u) {
            return { 0, 0 };
        }
        else if (u->tl == l && u->tr == r) {
            return u->val;
        }
        else {
            T tm = (u->tl + u->tr) / 2;

            return max(query(u->l, l, min(r, tm)), query(u->r, max(l, tm + 1), r));
        }
    }

    inline pair <T, T> query(T l, T r) {
        return query(root, l, r);
    }
};
