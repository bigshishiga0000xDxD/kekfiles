typedef long long ll;

const int INF = 2e9;

template <typename T, typename V, ll L, ll R>
struct Tree {
    struct Node {
        T val;
        V tl, tr;
        Node *l = nullptr, *r = nullptr;

        Node(V tl, V tr) : val(-INF), tl(tl), tr(tr) {}
    };

    Node* root = new Node(L, R);

    inline T get(Node* u) {
        return (u ? u->val : -INF);
    }

    inline void update(Node* u) {
        u->val = max(get(u->l), get(u->r));
    }

    void update(Node *u, V pos, T val) {
        if (u->tl == u->tr) {
            u->val = val;
        }
        else {
            V tm = (u->tl + u->tr) / 2;
            if (u->tl + u->tr < 0) tm--;

            if (pos <= tm) {
                if (!u->l) u->l = new Node(u->tl, tm);
                update(u->l, pos, val);
            }
            else {
                if (!u->r) u->r = new Node(tm + 1, u->tr);
                update(u->r, pos, val);
            }
            update(u);
        }
    }

    inline void update(V pos, T val) {
        update(root, pos, val);
    }

    T query(Node *u, V l, V r) {
        if (l > r || !u) {
            return -INF;
        }
        else if (u->tl == l && u->tr == r) {
            return u->val;
        }
        else {
            V tm = (u->tl + u->tr) / 2;

            return max(query(u->l, l, min(r, tm)), query(u->r, max(l, tm + 1), r));
        }
    }

    inline T query(V l, V r) {
        return query(root, l, r);
    }
};
