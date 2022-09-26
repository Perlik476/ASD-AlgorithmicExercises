#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
    vector<int> &array;
    size_t heap_size;

    static size_t parent(size_t index) {
        return (index + 1) / 2 - 1;
    }

    static size_t right_son(size_t index) {
        return 2 * (index + 1);
    }

    static size_t left_son(size_t index) {
        return 2 * (index + 1) - 1;
    }

    void heapify(size_t index) {
        size_t left = left_son(index);
        size_t right = right_son(index);
        size_t largest = 0;

        if (left < heap_size && array[left] > array[index]) {
            largest = left;
        }
        else {
            largest = index;
        }

        if (right < heap_size && array[right] > array[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(array[largest], array[index]);
            heapify(largest);
        }
    }
public:
    Heap(vector<int> &array) : array(array) {

    }

    vector<int> &build_heap() {
        heap_size = array.size();
        for (size_t index = array.size() / 2 - 1; index <= array.size() / 2 - 1; index--) {
            heapify(index);
        }
        return array;
    }

    void print_heap() {
        size_t power = 1;
        size_t current = 0;
        for (int elem : array) {
            cout << elem << " ";
            current++;
            if (current == power) {
                current = 0;
                power *= 2;
                cout << "\n";
            }
        }
        cout << "\n";
    }

    vector<int> &heapsort() {
        build_heap();

        print_heap();

        for (size_t index = array.size() - 1; index >= 1; index--) {
            swap(array[0], array[index]);
            heap_size--;
            heapify(0);
        }

        return array;
    }

};


int main() {
    vector<int> v{5,2,6,8,1,21,7,37};

    Heap heap(v);
    vector<int> &u = heap.heapsort();

    cout << "wypisywanko:\n";
    for (auto e : v) {
        cout << e << " ";
    }
    cout << "\n";
    for (auto e : u) {
        cout << e << " ";
    }

    return 0;
}
