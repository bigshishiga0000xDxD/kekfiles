typedef long long ll;
const ll INF = 1e18;
const int M = 1e9 + 1;

struct Line {
    ll k, b;

    ll eval(ll x) {
        return k * x + b;
    }
};

// dynamic Li Chao tree
// realizaciya gavno, no mne pox
struct Tree {
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        int tl, tr;
        Line ln = { 0, INF };

        Node(int tl, int tr) : tl(tl), tr(tr) {}

        ~Node() {
            delete l;
            delete r;
        }
    };

    Node *root = new Node(-M, M); // x range
    size_t _size = 1;

    ~Tree() {
        delete root;
    }

    inline bool create(Node *&u, int l, int r) {
        if (!u) {
            if (l > r) {
                return false;
            }
            else {
                u = new Node(l, r);
                _size++;
                return true;
            }
        }
        else {
            return true;
        }
    }

    void add(Node *u, Line l) { // add line
        int tm = (u->tl + u->tr) / 2;
        if (u->tl + u->tr < 0) {
            tm--;
        }

        bool left = l.eval(u->tl) < u->ln.eval(u->tl);
        bool mid = l.eval(tm) < u->ln.eval(tm);
        bool right = l.eval(u->tr) < u->ln.eval(u->tr);

        if (left && right) {
            u->ln = l;
        }
        else if (!left && !right) {
            return;
        }
        else if (!left && right) {
            if (mid) {
                if (create(u->l, u->tl, tm)) {
                    add(u->l, u->ln);
                }
                u->ln = l;
            }
            else {
                if (create(u->r, tm + 1, u->tr)) {
                    add(u->r, l);
                }
            }
        }
        else {
            if (mid) {
                if (create(u->r, tm + 1, u->tr)) {
                    add(u->r, u->ln);
                }
                u->ln = l;
            }
            else {
                if (create(u->l, u->tl, tm)) {
                    add(u->l, l);
                }
            }
        }
    } 

    ll get(Node *u, ll x) { // get min
        if (u) {
            int tm = (u->tl + u->tr) / 2;
            if (u->tl + u->tr < 0) {
                tm--;
            }

            if (x <= tm) {
                return min(get(u->l, x), u->ln.eval(x));
            }
            else {
                return min(get(u->r, x), u->ln.eval(x));
            }
        }
        else {
            return INF;
        }
    }

    void dfs(Node *u, vector <Line>& res) {
        if (u->ln.b != INF) {
            res.push_back(u->ln);
        }

        if (u->l) {
            dfs(u->l, res);
        }
        if (u->r) {
            dfs(u->r, res);
        }
    }

    vector <Line> get_list() {
        vector <Line> res;
        res.reserve(_size);

        dfs(root, res);

        return res;
    }

    inline size_t size() {
        return _size;
    }
};

