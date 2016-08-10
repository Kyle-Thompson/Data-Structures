#include "heap.h"
#include <iostream>
using namespace std;

int main() {
    heap<int> h;
    for (int i : {9, 8, 7, 6, 5, 4, 3, 2, 1}) {
        h.push(i);
    }

    while (!h.empty()) {
        h.get();
        h.pop();
    }
}
