#include "algorithm.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void pr(const vector<int>& v) {
    for (auto i : v) {
        cout << i << ", ";
    }
    cout << "\n";
}

int main() {
    vector<int> v({8, 7, 6, 5, 4, 3, 2, 1});

    ads::sort(v);

    pr(v);
}
