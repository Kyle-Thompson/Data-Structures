#include "redblack_tree.h"
#include <vector>
#include <iostream>

using namespace std;


int main() {
    std::vector<int> v { 2, 1, 3, 4, 5, 6, 7, 8 };
    redblack_tree<int> rbt;

    for (int i : v){
        rbt.push(i);
        rbt.print();
        cout << "\n\n";
    } 
}
