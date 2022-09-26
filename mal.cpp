#include <iostream>
#include <vector>

using namespace std;

enum TreeColor {
    Black, White, Mixed
};

class IntervalTree {
public:
    IntervalTree(int n) {
        number_of_elements = 1;
        while (number_of_elements < n) {
            number_of_elements *= 2;
        }
        white_count_array.resize(2 * number_of_elements, 0);
        colors_array.resize(2 * number_of_elements, Black);
    }

    int getValueInRoot() {
        return white_count_array[1];
    }

    void setValueOnInterval(char c, int a, int b) {
        setValueOnInterval(c == 'C' ? Black : White, a, b, 1, 0, number_of_elements - 1);
    }
private:
    int number_of_elements;
    vector<int> white_count_array;
    vector<TreeColor> colors_array;

    int parent(int index) {
        return index / 2;
    }

    int rightChild(int index) {
        return 2 * index + 1;
    }

    int leftChild(int index) {
        return 2 * index;
    }

    void setValueOnInterval(TreeColor color, int a, int b, int node_index, int node_left_interval, int node_right_interval) {
        if (a > node_right_interval || b < node_left_interval) {
            return;
        }
        else if (a <= node_left_interval && node_right_interval <= b) {
            colors_array[node_index] = color;
            white_count_array[node_index] = (color == White ? node_right_interval + 1 - node_left_interval : 0);
        }
        else {
            if (colors_array[node_index] != Mixed) {
                pushDown(node_index, node_left_interval, node_right_interval);
            }
            int middle = (node_left_interval + node_right_interval) / 2;
            setValueOnInterval(color, a, b, leftChild(node_index), node_left_interval, middle);
            setValueOnInterval(color, a, b, rightChild(node_index), middle + 1, node_right_interval);
            colors_array[node_index] = (colors_array[leftChild(node_index)] == colors_array[rightChild(node_index)] ?
                    colors_array[leftChild(node_index)] : Mixed);
            white_count_array[node_index] = white_count_array[leftChild(node_index)] + white_count_array[rightChild(node_index)];
        }
    }

    void pushDown(int node_index, int node_left_interval, int node_right_interval) {
        TreeColor color = colors_array[node_index];
        colors_array[leftChild(node_index)] = color;
        colors_array[rightChild(node_index)] = color;

        int middle = (node_left_interval + node_right_interval) / 2;
        white_count_array[leftChild(node_index)] = (color == White ? middle + 1 - node_left_interval : 0);
        white_count_array[rightChild(node_index)] = (color == White ? node_right_interval + 1 - (middle + 1) : 0);
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    IntervalTree tree(n);
    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        tree.setValueOnInterval(c, a, b);
        cout << tree.getValueInRoot() << "\n";
    }

    return 0;
}
