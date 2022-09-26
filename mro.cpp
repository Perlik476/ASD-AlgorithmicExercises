#include <vector>
#include <iostream>

const int LOG = 19;
const int _MAX_N = (1 << LOG);
const int BASE = _MAX_N;

int tree[_MAX_N << 1];
bool clear_subtree[_MAX_N << 1];


int point;
int value;
bool must_update;
int begin;
int end;


void update(int node) {
    if (clear_subtree[node]) {
        tree[node << 1] = 0;
        tree[(node << 1) + 1] = 0;

        clear_subtree[node << 1] = true;
        clear_subtree[(node << 1) + 1] = true;
    }

    clear_subtree[node] = false;
}


void add(int node, int cur_begin, int cur_end, int height) {
//    cout << node << " " << cur_begin << " " << cur_end << " " << point << "\n";
    if (point == cur_begin && cur_end == point){
        tree[node] += value * (1 << (height));
        return;
    }

    if (must_update) {
        update(node);
    }

    int mid = (cur_begin + cur_end) / 2;
    if (mid >= point) {
        add((node << 1), cur_begin, mid, height - 1);
    }
    else {
        add((node << 1) + 1, mid + 1, cur_end, height - 1);
    }

    tree[node] = tree[(node << 1)] + tree[(node << 1) + 1];
}

void add(int _point, int _value, bool _must_update) {
    point = _point;
    value = _value;
    must_update = _must_update;
    add(1, 0, BASE - 1, LOG);
}


int read_int(int node, int cur_begin, int cur_end) {
    if(cur_end < begin || end < cur_begin)
        return 0;

    if(begin <= cur_begin && cur_end <= end)
        return tree[node];

    update(node);

    int mid = (cur_begin + cur_end) / 2;

    int left_value = read_int((node << 1), cur_begin, mid);
    int right_value = read_int((node << 1) + 1, mid + 1, cur_end);

    return left_value + right_value;
}

int read(int _begin, int _end) {
    begin = _begin;
    end = _end;
    return read_int(1, 0, BASE - 1);
}

int read_point(int node, int cur_begin, int cur_end) {
    if (point == cur_begin && cur_end == point){
        return tree[node];
    }

    update(node);

    int mid = (cur_begin + cur_end) / 2;
    if (mid >= point) {
        return read_point((node << 1), cur_begin, mid);
    }
    else {
        return read_point((node << 1) + 1, mid + 1, cur_end);
    }
}

int read(int _point) {
    point = _point;
    return read_point(1, 0, BASE - 1);
}

void clear(int node, int cur_begin, int cur_end) {
    if(cur_end < begin || end < cur_begin)
        return;

    if(begin <= cur_begin && cur_end <= end){
        clear_subtree[node] = true;
        tree[node] = 0;
        return;
    }

    int mid = (cur_begin + cur_end) / 2;

    clear((node << 1), cur_begin, mid);
    clear((node << 1) + 1, mid + 1, cur_end);

    tree[node] = tree[(node << 1)] + tree[(node << 1) + 1];
}

void clear(int _begin, int _end) {
    begin = _begin;
    end = _end;
    clear(1, 0, BASE - 1);
}

int read_number() {
    int number = 0;

    int c;
    while (isdigit(c = getchar_unlocked())) {
        number *= 10;
        number += (c - '0');
    }

    return number;
}

void print_number(int a) {
    char str[32];
    int i = 0;
    if (a == 0) {
        str[i] = '0';
        i++;
    }
    else {
        while (a > 0) {
            str[i] = (a % 10) + '0';
            a /= 10;
            i++;
        }
    }

    for (int k = i - 1; k >= 0; k--) {
        putchar_unlocked(str[k]);
    }
    putchar_unlocked('\n');
}

int main(){
    std::ios_base::sync_with_stdio(false);

    int n, m;

//    std::cin >> n >> m;
    n = read_number();
    m = read_number();

    int x;
    for(int i = 1; i <= n; i++){
//        std::cin >> x;
        x = read_number();
        add(x, 1, false);
    }

    int l, r, d;
    while (m --> 0) {
//        std::cin >> l >> r >> d;
        l = read_number();
        r = read_number();
        d = read_number();
        int v = read(l, r);
        if (v == 0) {
//            std::cout << 0 << "\n";
            print_number(0);
        }
        else {
            int u = read(d);

//            std::cout << (v - u) << "\n";
            x = v - u;
            print_number(x);

            clear(l, r);
            add(d, v, true);
        }
    }

    return 0;
}