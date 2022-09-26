#include <iostream>

using namespace std;

const int mod = 1e9;

class IntervalTree {
public:
    void init(int number_of_elements);
    void modify(int index, int value);
    int query(int left, int right);
    void destroy();
    void print();

private:
    int size;
    int number_of_elements;
    int *array;
    int parent(int index);
    int left_son(int index);
    int right_son(int index);
    int element_in_tree(int original_index);
    bool is_root(int index);
    int query(int left, int right, int index, int index_interval_left, int index_interval_right);
};

void IntervalTree::modify(int index, int value) {
    index = element_in_tree(index);
    array[index] = value;

    while (!is_root(index)) {
        index = parent(index);
        array[index] = (array[right_son(index)] + array[left_son(index)]) % mod;
    }
}

int IntervalTree::query(int left, int right) {
    return query(left, right, 1, 0, number_of_elements - 1);
}

int IntervalTree::query(int left, int right, int index, int index_interval_left, int index_interval_right) {
    if (left <= index_interval_left && index_interval_right <= right) {
        return array[index];
    }
    else if (left > index_interval_right || right < index_interval_left) {
        return 0;
    }
    else {
        int middle = (index_interval_left + index_interval_right) / 2;
        return (query(left, right, left_son(index), index_interval_left, middle)
                + query(left, right, right_son(index), middle + 1, index_interval_right)) % mod;
    }
}

void IntervalTree::init(int number_of_elements) {
    int power = 1;
    while (power < 2 * n) {
        power = power << 1;
    }
    size = power;
    number_of_elements = size / 2;

    array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

int IntervalTree::parent(int index) {
    return index / 2;
}

int IntervalTree::left_son(int index) {
    return 2 * index;
}

int IntervalTree::right_son(int index) {
    return 2 * index + 1;
}

int IntervalTree::element_in_tree(int original_index) {
    return original_index + number_of_elements;
}

bool IntervalTree::is_root(int index) {
    return index == 1;
}

void IntervalTree::destroy() {
    delete array;
}

void IntervalTree::print() {
    int power = 1;
    for (int i = 0; i < size; i++) {
        cout << array[i] << (i + 1 == power ? "\n" : " ");
        if (i + 1 == power) {
            power *= 2;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int T[n][k + 1];
    for (int i = 0; i < n; i++) {
        T[i][1] = 1;
    }

    for (int l = 2; l <= k; l++) {
        IntervalTree tree{};
        tree.init(n);

        for (int i = 0; i < n; i++) {
            T[i][l] = tree.query(a[i], n - 1);
            tree.modify(a[i] - 1, T[i][l - 1]);
        }

        tree.destroy();
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = (sum + T[i][k]) % mod;
    }
    cout << sum;

    return 0;
}
