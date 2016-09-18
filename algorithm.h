#ifndef ALGORITHM_H
#define ALGORITHM_H

/*
 * Functions:
 *    sort
 * 
 */

#include <vector>
#include <array>
#include <iostream>
#include <memory>
using namespace std;


namespace ads {

// template <class T> // replace all int with T
std::vector<int>&
sort(std::vector<int>& v)
{
    std::allocator<int> alloc;
    std::size_t size = v.size();
    int* store = (int*) malloc(size*sizeof(int));
//    int* store = alloc.allocate(size);
    
    auto merge = [&](std::size_t index, std::size_t len) { // TODO make this use constant extra space.
        cout << "merging index " << index << " and len " << len << "\n";
        std::size_t end = (len < size ? len : size), mid = len/2;
        
        std::size_t l = index, r = index + mid;
        for (std::size_t i = 0; i < end; ++i) {
            if (l == mid) {
                store[i] = v[r++];
            } else if (r == end) {
                store[i] = v[l++];
            } else if (v[l] < v[r]) {
                store[i] = v[l++];
            } else {
                store[i] = v[r++];
            } 
        }

        for (std::size_t i = 0; i < end; ++i)
            v[index + i] = store[i];
    };
    
    for (std::size_t i = 1; i < size;) {
        i *= 2;
        for (std::size_t j = 0; j < size + i /* unsure about this */; j += i) {
            merge(j, i);
        }
    }

    //alloc.deallocate(store, size);
    free(store);
    return v;
}

}

#endif
