
#include <iostream>

#include "list.h"

int main() {
    ads::list<int> l({4, 3, 6, 1});
    l.push_back(2);
    l.remove(3);

    for (int i : l) {
        std::cout << i << "\n";
    }
}

