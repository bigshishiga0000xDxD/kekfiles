struct treap {
    private: struct Node {
        int val, pr, cnt;
        Node *l, *r;

        Node() {}
        Node(int val) : val(val), pr(rng()), cnt(1), l(nullptr), r(nullptr) {}
    };

    private: int get(Node* u) {
        if (u) {
            return u->cnt;
        }
        else {
            return 0;        
        }
    }

    private: void update(Node* u) {
        if (u) {
            u->cnt = get(u->l) + get(u->r) + 1;
        }
    }


    private: Node* root;
    
    public: treap() : root(nullptr) {}


    private: pair <Node*, Node*> split(Node* u, int k) {
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

    private: Node* merge(Node* u, Node* v) {
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
            v->l = (u, v->l);

            update(v);
            return v;
        }
    }
};
