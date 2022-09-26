#include <iostream>
#include <cassert>
#include <vector>

template <typename V>
class Node;

template<typename V>
void update(Node<V> *node) {
    if (node != nullptr) {
        node->_update();
    }
}

template<typename V>
int get_how_many_mod_3(Node<V> *node, int i) {
    if (node != nullptr) {
        return node->_get_how_many_mod_3(i);
    }
    return 0;
}

template<typename V>
int get_how_many_mod_3_max_right(Node<V> *node, int i) {
    if (node != nullptr) {
        return node->_get_how_many_mod_3_max_right(i);
    }
    return 0;
}

template<typename V>
int get_how_many_mod_3_max_left(Node<V> *node, int i) {
    if (node != nullptr) {
        return node->_get_how_many_mod_3_max_left(i);
    }
    return 0;
}

template<typename V>
int get_sum(Node<V> *node) {
    if (node != nullptr) {
        return node->_get_sum();
    }
    return 0;
}

template <typename V>
class Node {
    using parents_t = std::vector<Node *>;

    Node *right, *left;
    V value;
    int how_many_mod_3[3];
    int sum;
    int how_many_mod_3_max_right[3];
    int how_many_mod_3_max_left[3];

    void rotate_right(Node *parent, Node *grand_parent) {
        assert(parent->left == this);
        parent->left = this->right;
        update(parent);
        this->right = parent;
        update(this);
        if (grand_parent != nullptr) {
            assert(grand_parent->left == parent || grand_parent->right == parent);
            if (grand_parent->left == parent) {
                grand_parent->left = this;
            }
            else {
                grand_parent->right = this;
            }
        }
    }

    void rotate_left(Node *parent, Node *grand_parent) {
        assert(parent->right == this);
        parent->right = this->left;
        update(parent);
        this->left = parent;
        update(this);
        if (grand_parent != nullptr) {
            assert(grand_parent->left == parent || grand_parent->right == parent);
            if (grand_parent->left == parent) {
                grand_parent->left = this;
            }
            else {
                grand_parent->right = this;
            }
        }
    }

    size_t static local_splay(Node *node, parents_t parents, size_t index) {
//        std::cout << "local_splay(" << node->get_value() << ", " << parents.size() << ", " << index << ") " << std::endl;
        if (index == 0) { // ojciec node'a to root
            parents[index]->print();
            assert(parents[index]->get_left() == node || parents[index]->get_right() == node);
            if (parents[index]->get_left() == node) {
                node->rotate_right(parents[index], nullptr);
            }
            else {
                node->rotate_left(parents[index], nullptr);
            }
            return 1;
        }
        else {
            if (parents[index]->get_left() == node && parents[index - 1]->get_left() == parents[index]) {
//                std::cout << "double_right" << std::endl;
                parents[index]->rotate_right(parents[index - 1], index - 1 > 0 ? parents[index - 2] : nullptr);
                node->rotate_right(parents[index], index - 1 > 0 ? parents[index - 2] : nullptr);
            }
            else if (parents[index]->get_right() == node && parents[index - 1]->get_right() == parents[index]) {
//                std::cout << "double_left" << std::endl;
                parents[index]->rotate_left(parents[index - 1], index - 1 > 0 ? parents[index - 2] : nullptr);
                node->rotate_left(parents[index], index - 1 > 0 ? parents[index - 2] : nullptr);
            }
            else if (parents[index]->get_right() == node && parents[index - 1]->get_left() == parents[index]) {
//                std::cout << "left_right" << std::endl;
                node->rotate_left(parents[index], parents[index - 1]);
                node->rotate_right(parents[index - 1], index - 1 > 0 ? parents[index - 2] : nullptr);
            }
            else if (parents[index]->get_left() == node && parents[index - 1]->get_right() == parents[index]) {
//                std::cout << "right_left" << std::endl;
                node->rotate_right(parents[index], parents[index - 1]);
                node->rotate_left(parents[index - 1], index - 1 > 0 ? parents[index - 2] : nullptr);
            }
            return 2;
        }
    }

    void static splay(Node *node, parents_t &parents, size_t index) {
//        std::cout << "splay" << std::endl;
        while (index + 1 != 0) {
            std::cout << std::endl;
            parents[0]->print_all();
            std::cout << std::endl;

            index -= local_splay(node, parents, index);
        }
//        std::cout << "splay: end" << std::endl;
    }

public:
    explicit Node(V _value) : value(_value) {
        right = nullptr;
        left = nullptr;
        for (int i = 0; i < 3; i++) {
            how_many_mod_3[i] = 0;
            how_many_mod_3_max_left[i] = 0;
            how_many_mod_3_max_right[i] = 0;
        }
        sum = 0;
        how_many_mod_3[value % 3] = 1;
        how_many_mod_3_max_left[value % 3] = 1;
        how_many_mod_3_max_right[value % 3] = 1;
    }

    void set_left(Node *node) {
        left = node;
    }

    void set_right(Node *node) {
        right = node;
    }

    Node *get_left() {
        return left;
    }

    Node *get_right() {
        return right;
    }

    V get_value() {
        return value;
    }

    void print() {
        std::cout << value << ": left: " << (left != nullptr ? left->get_value() : -1) << ", right: "
                  << (right != nullptr ? right->get_value() : -1) << std::endl;
    }

    void print_all() {
        print();
        if (left != nullptr) {
            left->print_all();
        }
        if (right != nullptr) {
            right->print_all();
        }
    }

    void set_value(V _value) {
        value = _value;
    }

    Node *search(V v) {
        parents_t parents;
        parents.reserve(30);
        return search(v, parents);
    }

    Node *search(V v, parents_t &parents) {
//        std::cout << "current: " << this->get_value() << std::endl;
        if (v < this->value) {
            if (this->left != nullptr) {
                parents.push_back(this);
                return this->left->search(v, parents);
            }
            else {
                splay(this, parents, parents.size() - 1);
                return nullptr;
            }
        }
        else if (v > this->value) {
            if (this->right != nullptr) {
                parents.push_back(this);
                return this->right->search(v, parents);
            }
            else {
                splay(this, parents, parents.size() - 1);
                return nullptr;
            }
        }
        else {
            splay(this, parents, parents.size() - 1);
            return this;
        }
    }

    Node *insert(V v) {
        parents_t parents;
        parents.reserve(30);
        return insert(v, parents);
    }

    Node *insert(V v, parents_t &parents) {
        Node *node = nullptr;
//        std::cout << "current: " << this->get_value() << std::endl;
        if (v < this->value) {
            if (this->left != nullptr) {
                parents.push_back(this);
                return this->left->insert(v, parents);
            }
            else {
                parents.push_back(this);
                node = new Node(v);
                this->left = node;
                splay(node, parents, parents.size() - 1);
                return node;
            }
        }
        else if (v > this->value) {
            if (this->right != nullptr) {
                parents.push_back(this);
                return this->right->insert(v, parents);
            }
            else {
                parents.push_back(this);
                node = new Node(v);
                this->right = node;
                splay(node, parents, parents.size() - 1);
                return node;
            }
        }
        else {
            splay(this, parents, parents.size() - 1);
            return this;
        }
    }


    std::pair<size_t, Node *> query(size_t pos_begin, size_t pos_end) {
        Node *node = this;

        node = node->search(pos_end);
        Node *right_side = node->right;
        node->right = nullptr;
        update(node);

        node = node->search(pos_begin);
        Node *left_side = node->left;
        node->left = nullptr;
        update(node);

        size_t result = get_max_subsequence(node);

        node->left = left_side;
        update(node);

        node = node->search(pos_end);
        node->right = right_side;
        update(node);

        return {result, node};
    }

    int _get_how_many_mod_3(int i) {
        assert(i >= 0 && i <= 2);
        return how_many_mod_3[i];
    }

    int _get_how_many_mod_3_max_right(int i) {
        assert(i >= 0 && i <= 2);
        return how_many_mod_3_max_right[i];
    }

    int _get_how_many_mod_3_max_left(int i) {
        assert(i >= 0 && i <= 2);
        return how_many_mod_3_max_left[i];
    }

    int _get_sum() {
        return sum;
    }

    void _update() {
        sum = get_sum(left) + get_sum(right);

        if (value % 3 == 0) {
            how_many_mod_3[0] = get_how_many_mod_3(left, 0) + get_how_many_mod_3(right, 0)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                - 2;

            how_many_mod_3[1] = get_how_many_mod_3(left, 1) + get_how_many_mod_3(right, 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                - 3;

            how_many_mod_3[2] = get_how_many_mod_3(left, 2) + get_how_many_mod_3(right, 2)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                - 3;

            how_many_mod_3_max_right[0] = get_how_many_mod_3_max_right(right, 0) + ((get_sum(right) + value) % 3 == 0)
                                * (1 + get_how_many_mod_3_max_right(left, 0));
        }
        else if (value % 3 == 1) {
            how_many_mod_3[0] = get_how_many_mod_3(left, 0) + get_how_many_mod_3(right, 0)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                - 3;

            how_many_mod_3[1] = get_how_many_mod_3(left, 1) + get_how_many_mod_3(right, 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                - 2;

            how_many_mod_3[2] = get_how_many_mod_3(left, 2) + get_how_many_mod_3(right, 2)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                - 3;
        }
        else {
            how_many_mod_3[0] = get_how_many_mod_3(left, 0) + get_how_many_mod_3(right, 0)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                - 3;

            how_many_mod_3[1] = get_how_many_mod_3(left, 1) + get_how_many_mod_3(right, 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                - 3;

            how_many_mod_3[2] = get_how_many_mod_3(left, 2) + get_how_many_mod_3(right, 2)
                                + (get_how_many_mod_3_max_right(left, 2) + 1) * (get_how_many_mod_3_max_left(right, 1) + 1)
                                + (get_how_many_mod_3_max_right(left, 1) + 1) * (get_how_many_mod_3_max_left(right, 2) + 1)
                                + (get_how_many_mod_3_max_right(left, 0) + 1) * (get_how_many_mod_3_max_left(right, 0) + 1)
                                - 2;
        }
    }

};


int main() {
    Node<int> root = Node(5);
    Node<int> right = Node(7);
    Node<int> left = Node(2);
    root.set_right(&right);
    root.set_left(&left);
    Node<int> left_left = Node(1);
    Node<int> left_right = Node(4);
    left.set_left(&left_left);
    left.set_right(&left_right);
    Node<int> left_left_left = Node(0);
    left_left.set_left(&left_left_left);

    Node<int> *result = root.search(0);
    result->print_all();

    result = result->search(4);
    result->print_all();

    result = result->insert(3);
    result->print_all();
//    std::cout << left.get_right()->get_value();

    return 0;
}