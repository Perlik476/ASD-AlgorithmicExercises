#include <iostream>
#include <cassert>
#include <vector>

#define assert(x) do {} while(false)

template <typename V>
class Node;


template <typename V>
size_t get_max_subsequence(std::vector<V> seq, size_t pos_begin, size_t pos_end);


template<typename V>
size_t get_size_of_subtree(Node<V> *node) {
    return node == nullptr ? 0 : node->give_size_of_subtree();
}

template<typename V>
size_t get_max_subsequence_right(Node <V> *node) {
    return node == nullptr ? 0 : node->give_max_subsequence_right();
}

template<typename V>
size_t get_max_subsequence_left(Node <V> *node) {
    return node == nullptr ? 0 : node->give_max_subsequence_left();
}

template<typename V>
size_t get_max_subsequence(Node <V> *node) {
    return node == nullptr ? 0 : node->give_max_subsequence();
}

template<typename V>
void update(Node<V> *node) {
    if (node != nullptr) {
        node->_update_size_of_subtree();
        node->_update_rotation();
    }
}


template<typename V>
void change_rotation(Node<V> *node) {
    if (node != nullptr) {
        node->_change_rotation();
    }
}

template<typename V>
void update_rotation(Node<V> *node) {
    update_rotation(node, true);
}

template<typename V>
void update_rotation(Node<V> *node, bool deeper) {
    if (node != nullptr) {
        node->_update_rotation(deeper);
    }
}


template <typename V>
class Node {
    using parents_t = std::vector<Node *>;

    Node *right, *left;
    V value;
    size_t size_of_subtree;
    V max_right, max_left;
    size_t max_subsequence, max_subsequence_right, max_subsequence_left;
    bool must_rotate;

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

    size_t static local_splay(Node *node, parents_t &parents, size_t parents_index) {
        if (parents_index == 0) { // ojciec node'a to root
            assert(parents[parents_index]->get_left() == node || parents[parents_index]->get_right() == node);
            if (parents[parents_index]->get_left() == node) {
                node->rotate_right(parents[parents_index], nullptr);
            }
            else {
                node->rotate_left(parents[parents_index], nullptr);
            }
            return 1;
        }
        else {
            Node *parent = parents[parents_index];
            Node *grand_parent = parents[parents_index - 1];
            Node *grand_grand_parent = parents_index - 1 > 0 ? parents[parents_index - 2] : nullptr;

            if (parents[parents_index]->get_left() == node && parents[parents_index - 1]->get_left() == parents[parents_index]) {
                parent->rotate_right(grand_parent, grand_grand_parent);
                node->rotate_right(parent, grand_grand_parent);
            }
            else if (parents[parents_index]->get_right() == node && parents[parents_index - 1]->get_right() == parents[parents_index]) {
                parent->rotate_left(grand_parent, grand_grand_parent);
                node->rotate_left(parent, grand_grand_parent);
            }
            else if (parents[parents_index]->get_right() == node && parents[parents_index - 1]->get_left() == parents[parents_index]) {
                node->rotate_left(parent, grand_parent);
                node->rotate_right(grand_parent, grand_grand_parent);
            }
            else if (parents[parents_index]->get_left() == node && parents[parents_index - 1]->get_right() == parents[parents_index]) {
                node->rotate_right(parent, grand_parent);
                node->rotate_left(grand_parent, grand_grand_parent);
            }
            return 2;
        }
    }

    void static splay(Node *node, parents_t &parents, size_t parents_index) {
        while (parents_index + 1 != 0) {
            parents_index -= local_splay(node, parents, parents_index);
        }
    }

    void destroy() {
        if (left != nullptr) {
            left->destroy();
        }
        if (right != nullptr) {
            right->destroy();
        }
        delete this;
    }

public:
    explicit Node(V _value) : value(_value) {
        right = nullptr;
        left = nullptr;
        size_of_subtree = 1;
        max_right = value;
        max_left = value;
        max_subsequence = 1;
        max_subsequence_left = 1;
        max_subsequence_right = 1;
        must_rotate = false;
    }

    ~Node() {
        destroy();
    }

    void _update_size_of_subtree() {
        size_of_subtree = 1 + get_size_of_subtree(right) + get_size_of_subtree(left);
    }

    void _update_max_left() {
        max_left = left != nullptr ? left->max_left : value;
    }

    void _update_max_right() {
        max_right = right != nullptr ? right->max_right : value;
    }


    void _update_max_subsequence() {
        max_subsequence = std::max(
                left != nullptr ? left->max_subsequence : 1, std::max(
                        right != nullptr ? right->max_subsequence : 1,
                        1 + (left != nullptr ? (left->max_right == value) * left->max_subsequence_right : 0)
                        + (right != nullptr ? (right->max_left == value) * right->max_subsequence_left : 0)));
    }

    void _update_max_subsequence_right() {
        max_subsequence_right = get_max_subsequence_right(right)
                                + (get_max_subsequence_right(right) == get_size_of_subtree(right) ? (
                + (value == max_right ? (
                        1 + (left == nullptr ? 0 : (left->max_right == max_right ? left->max_subsequence_right : 0))
                ) : 0)
        ) : 0);
    }

    void _update_max_subsequence_left() {
        max_subsequence_left = get_max_subsequence_left(left)
                               + (get_max_subsequence_left(left) == get_size_of_subtree(left) ? (
                + (value == max_left ? (
                        1 + (right == nullptr ? 0 : (right->max_left == max_left ? right->max_subsequence_left : 0))
                ) : 0)
        ) : 0);
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
        std::cout << value << ": left: " << (left != nullptr ? left->get_value() : ' ') << ", right: "
                  << (right != nullptr ? right->get_value() : ' ') << ", subtree: " << size_of_subtree
                  << ", max_left: " << max_left << ", max_right: " << max_right << ", max_sub: " << max_subsequence
                  << ", max_sub_left: " << max_subsequence_left << ", max_sub_right: " << max_subsequence_right << std::endl;
    }

    void print_all() {
        print_all2();
        std::cout << std::endl;
    }

    void print_all2() {
        print();
        if (left != nullptr) {
            left->print_all2();
        }
        if (right != nullptr) {
            right->print_all2();
        }
    }

    void print_sequence() {
        _print_sequence();
        std::cout << std::endl;
    }

    void _print_sequence() {
        if (left != nullptr)
            left->_print_sequence();
        std::cout << this->value << ", ";
        if (right != nullptr)
            right->_print_sequence();
    }

    void set_value(V _value) {
        value = _value;
    }

    void _change_rotation() {
        must_rotate = 1 - must_rotate;
    }

    size_t give_size_of_subtree() {
        return size_of_subtree;
    }

    size_t give_max_subsequence() {
        return max_subsequence;
    }

    size_t give_max_subsequence_right() {
        return max_subsequence_right;
    }

    size_t give_max_subsequence_left() {
        return max_subsequence_left;
    }

    Node *search(size_t position) {
        parents_t parents;
        parents.reserve(100);
        return search(position, parents);
    }

    Node *search(size_t position, parents_t &parents) {
        assert(position >= 1);
        update_rotation(this);
        if (position < get_size_of_subtree(this->left) + 1) {
            if (this->left != nullptr) {
                parents.push_back(this);
                return this->left->search(position, parents);
            }
            else {
                splay(this, parents, parents.size() - 1);
                return nullptr;
            }
        }
        else if (position > get_size_of_subtree(this->left) + 1) {
            if (this->right != nullptr) {
                parents.push_back(this);
                return this->right->search(position - get_size_of_subtree(this->left) - 1, parents);
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

    Node *insert(V v, size_t position) {
        parents_t parents;
        parents.reserve(100);
        return insert(v, position, parents);
    }

    Node *insert(V v, size_t position, parents_t &parents) {
        assert(position >= 1);
        update_rotation(this);
        Node *node = nullptr;
        if (position < get_size_of_subtree(this->left) + 1) {
            this->size_of_subtree++; // zakładamy, że elementu nie ma w drzewie
            if (this->left != nullptr) {
                parents.push_back(this);
                return this->left->insert(v, position, parents);
            }
            else {
                parents.push_back(this);
                node = new Node(v);
                this->left = node;
                splay(node, parents, parents.size() - 1);
                return node;
            }
        }
        else if (position > get_size_of_subtree(this->left) + 1) {
            this->size_of_subtree++; // zakładamy, że elementu nie ma w drzewie
            if (this->right != nullptr) {
                parents.push_back(this);
                return this->right->insert(v, position - get_size_of_subtree(this->left) - 1, parents);
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
            node = new Node(v);
            node->right = this;
            node->left = this->left;
            this->left = nullptr;
            update(this);
            update(node);
            if (!parents.empty()) {
                if (parents[parents.size() - 1]->get_left() == this)
                    parents[parents.size() - 1]->left = node;
                else
                    parents[parents.size() - 1]->right = node;
            }
            node->print_all();
            splay(node, parents, parents.size() - 1);
            return node;
        }
    }

    Node *move(size_t pos_begin, size_t pos_end, size_t pos_after) {
        if (pos_end - pos_begin + 1 == this->size_of_subtree) {
            return this;
        }

        Node *temp = this->search(pos_end);

        Node *left_side, *right_side;

        right_side = temp->right;
        temp->right = nullptr;
        update(right_side);
        update(temp);

        temp = temp->search(pos_begin);

        left_side = temp->left;
        temp->left = nullptr;
        update(left_side);
        update(temp);

        Node *new_node;
        if (left_side != nullptr) {
            new_node = left_side;
            new_node = new_node->search(pos_begin - 1);
            new_node->right = right_side;
            update(new_node);
        }
        else { // (right_side != nullptr)
            new_node = right_side;
        }

        if (pos_after == new_node->size_of_subtree + 1) {
            new_node = new_node->search(pos_after - 1);
            new_node->right = temp;
            update(new_node);
            return new_node;
        }

        new_node = new_node->search(pos_after);
        left_side = new_node->left;
        new_node->left = temp;
        update(new_node);

        new_node = new_node->search(1);
        new_node->left = left_side;
        update(new_node);

        return new_node;
    }

    void rotate_recursive() {
        std::swap(left, right);
        if (left != nullptr)
            left->rotate_recursive();
        if (right != nullptr)
            right->rotate_recursive();
        update(this);
    }

    void _update_rotation() {
        _update_rotation(true);
    }

    void _update_rotation(bool deeper) {
        if (must_rotate) {
            _change_rotation();
            change_rotation(left);
            change_rotation(right);
            std::swap(left, right);
            std::swap(max_subsequence_right, max_subsequence_left);
            std::swap(max_right, max_left);
        }
        if (deeper) {
            update_rotation(left, false);
            update_rotation(right, false);
        }
    }

    Node *rotate(size_t pos_begin, size_t pos_end) {
        if (pos_end - pos_begin + 1 == this->size_of_subtree) {
            this->rotate_recursive();
            return this;
        }
        size_t pos_after = pos_begin;

        Node *temp = this->search(pos_end);

        Node *left_side, *right_side;

        right_side = temp->right;
        temp->right = nullptr;
        update(right_side);
        update(temp);

        temp = temp->search(pos_begin);

        left_side = temp->left;
        temp->left = nullptr;
        update(left_side);
        update(temp);

//        temp->rotate_recursive();
        change_rotation(temp);
        update_rotation(temp);

        Node *new_node;
        if (left_side != nullptr) {
            new_node = left_side;
            new_node = new_node->search(pos_begin - 1);
            new_node->right = right_side;
            update(new_node);
        }
        else { // (right_side != nullptr)
            new_node = right_side;
        }


        if (pos_after == new_node->size_of_subtree + 1) {
            new_node = new_node->search(pos_after - 1);
            new_node->right = temp;
            update(new_node);
            return new_node;
        }

        new_node = new_node->search(pos_after);
        left_side = new_node->left;
        new_node->left = temp;
        update(new_node);

        new_node = new_node->search(1);
        new_node->left = left_side;
        update(new_node);

        return new_node;
    }

    std::vector<V> get_sequence() {
        std::vector<V> seq;
        get_sequence(seq);
        return seq;
    }

    void get_sequence(std::vector<V> &seq) {
        if (left != nullptr)
            left->get_sequence(seq);
        seq.push_back(value);
        if (right != nullptr)
            right->get_sequence(seq);
    }

    size_t subsequence2(size_t pos_begin, size_t pos_end) {
        std::vector<V> seq = get_sequence();
        return get_max_subsequence(seq, pos_begin, pos_end);
    }

    std::pair<size_t, Node *> subsequence(size_t pos_begin, size_t pos_end, size_t offset) {
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

    std::pair<size_t, Node *> subsequence(size_t pos_begin, size_t pos_end) {
        return subsequence(pos_begin, pos_end, 0);
    }
};

// Mateusz Perlik
// rozwiązanie to zmodyfikowany kod zadania zaliczeniowego "dinozaur"

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;

    auto *root = new Node<char>(s[0]);
    for (int i = 2; i <= n; i++) {
        root = root->insert(s[i - 1], i);
    }

    root = root->search(1);

    for (int i = 0; i < m; i++) {
        int j, k;
        std::cin >> j >> k;
        root = root->rotate(j, k);
    }

    for (int i = 1; i <= n; i++) {
        root = root->search(i);
        std::cout << root->get_value();
    }

    return 0;
}
