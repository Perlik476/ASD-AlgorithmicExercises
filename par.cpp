#include <iostream>
#include <vector>

using namespace std;

class Node {
private:
    int id;
    Node *parent;
    Node *left_son;
    Node *right_son;

public:
    Node(int id, Node *left_son, Node *right_son, Node *parent) {
        this->id = id;
        this->left_son = left_son;
        this->right_son = right_son;
        this->parent = parent;
    }

    explicit Node(int id) {
        this->id = id;
        this->left_son = nullptr;
        this->right_son = nullptr;
        this->parent = nullptr;
    }

    Node* get_left_son() {
        return left_son;
    }

    Node* get_right_son() {
        return right_son;
    }

    void set_left_son(Node *left_son) {
        this->left_son = left_son;
    }

    void set_right_son(Node *right_son) {
        this->right_son = right_son;
    }

    void set_parent(Node *parent) {
        this->parent = parent;
    }
};

class Tree {
private:
    int number_of_nodes;
    vector<Node *> nodes_array;
public:
    explicit Tree(int n) {
        number_of_nodes = n;
        nodes_array.resize(number_of_nodes + 1);

        for (int i = 1; i <= n; i++) {
            nodes_array[i] = new Node(i);
        }
    }

    void set_node(int node_id, int left_son, int right_son) {
        nodes_array[node_id]->set_left_son(left_son == -1 ? nullptr : nodes_array[left_son]);
        nodes_array[node_id]->set_right_son(right_son == -1 ? nullptr : nodes_array[right_son]);
        if (left_son != -1)
            nodes_array[left_son]->set_parent(nodes_array[node_id]);
        if (right_son != -1)
            nodes_array[right_son]->set_parent(nodes_array[node_id]);
    }

};

pair<int, pair<Node *, Node *>> get_diamater(Node *node) {
    auto left_result = node->get_left_son() == nullptr ? get_diamater(node->get_left_son());
}


int main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n;

    Tree tree(n);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        tree.set_node(i, a, b);
    }




    return 0;
}
