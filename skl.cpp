#include <iostream>
#include <bits/stdc++.h>

std::vector<int> masks;
std::vector<int> count;
std::vector<int> parent;
std::vector<int> size;

int Find(int x) {
    if (parent[x] == x) {
        return x;
    }
    else {
        return parent[x] = Find(parent[x]);
    }
}

void Union(int x, int y) {
    if (size[Find(x)] >= size[Find(y)]) {
        parent[Find(y)] = Find(x);
        size[Find(x)] += size[Find(y)];
    }
    else {
        parent[Find(x)] = Find(y);
        size[Find(y)] += size[Find(x)];
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int mask = 0;

    for (int i = 0; i < 32; i++) {
        masks.push_back(mask);
        count.push_back(0);
        parent.push_back(i);
        size.push_back(0);
//        std::cout << mask << "\n";
        if (mask == 0) {
            mask = 1;
        }
        else {
            mask = mask << 1;
        }
    }

//    for (auto cur_mask : masks) {
//        std::cout << cur_mask << " ";
//    }

    int zeros_cnt = 0;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;

        int temp;
        std::vector<int> for_union;
        if (x == 0) {
            zeros_cnt++;
        }
        else {
            for (int j = 1; j < masks.size(); j++) {
                temp = x & masks[j];
//            std::cout << x << " " << masks[j] << " " << temp << std::endl;
                if (temp != 0) {
                    for_union.push_back(j);
                }
            }
        }

//        std::cout << for_union.size() << std::endl;

        if (!for_union.empty()) {
            int prev_mask = for_union[0];
            int next_mask;
            for (int j = 1; j < for_union.size(); j++) {
//                std::cout << j << std::endl;
                next_mask = for_union[j];
                Union(prev_mask, next_mask);
                prev_mask = next_mask;
            }
            count[Find(prev_mask)]++;
        }
    }

    std::set<int> used_masks;
    for (int i = 0; i < masks.size(); i++) {
//        std::cout << i << std::endl;
        if (count[Find(i)] > 0) {
            used_masks.insert(Find(i));
        }
    }
//    for (auto x : used_masks) {
//        std::cout << x << " ";
//    }
//    std::cout << "\n";

    std::cout << used_masks.size() + zeros_cnt << "\n";

    return 0;
}
