#include <vector>
#include <cstring>
#include <string>
#include <queue>
#include <tuple>

using std::string;
using std::tuple;
using std::queue;

struct Trie {
    struct Node {
        Node *g[26], *go[26], *sufflink = nullptr;
        bool term = false;

        Node() {
            memset(g, 0, sizeof g);
            memset(go, 0, sizeof go);
        }
    };

    inline Node*& to(Node* u, char c) {
        return u->g[c - 'a'];
    }

    inline Node*& go(Node* u, char c) {
        return u->go[c - 'a'];
    }

    Node *root = new Node();

    void add(const string& s, int i) {
        auto cur = root;

        for (char c : s) {
            if (!to(cur, c)) {
                to(cur, c) = new Node();
            }
            cur = to(cur, c);
        }

        cur->term = true;
    }

    void calc_sufflinks() {
        queue <tuple <Node*, Node*, char>> q;
        q.emplace(root, nullptr, 0);

        while (!q.empty()) {
            auto [u, p, ch] = q.front();
            q.pop();

            if (u == root || p == root) {
                u->sufflink = root; 
            }
            else {
                u->sufflink = go(p->sufflink, ch);
            }

            for (char c = 'a'; c <= 'z'; c++) {
                if (to(u, c)) {
                    go(u, c) = to(u, c);
                    q.emplace(to(u, c), u, c);
                }
                else {
                    go(u, c) = (u == root ? root : go(u->sufflink, c));
                }
            }
        }
    }
};
