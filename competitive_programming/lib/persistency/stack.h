#include <vector>

using std::vector;

template <typename T>
struct Stack {
    struct Node {
        Node* parent;
        T val;
        int size;

        Node(Node* u, const T& x) : parent(u), val(x), size(parent ? parent->size + 1 : 1) {}
    };

    Stack() {}

    private: vector <Node*> nodes = { nullptr };

    public: inline int size(int i) {
        return nodes[i] ? nodes[i]->size : 0;
    }

    inline void push(int i, const T& x) {
        nodes.push_back(new Node(nodes[i], x));
    }

    inline void pop(int i) {
        nodes.push_back(nodes[i]->parent);
    }

    inline T& top(int i) {
        return nodes[i]->val;
    }
};
