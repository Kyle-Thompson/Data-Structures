#include "algorithm.h"
#include <vector>
#include <algorithm>
#include <iostream>


void pr(const std::vector<int>& v) {
    for (auto i : v) {
        std::cout << i << ", ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> v({8, 7, 6, 5, 4, 3, 2, 1});

    std::cout << "test\n";
    ads::sort(v);

    pr(v);
}
