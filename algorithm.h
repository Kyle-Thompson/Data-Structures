//#ifndef ALGORITHM_H
//#define ALGORITHM_H

/*
 * Functions:
 *    sort
 * 
 */

// delete all these includes later.
#include <vector>
#include <array>
#include <iostream>
#include <memory>
using namespace std;


namespace ads {

// template <class T> // replace all int with T
std::vector<int>&
sort(std::vector<int>& v) // sort(ads::container<T>& v)
{
    std::allocator<int> alloc;
    auto size = v.size();
    int store[1000]; // TODO delete when using only constant extra space.
    
    auto merge = [&](std::size_t index, std::size_t len) { // TODO make this use constant extra space.
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

    return v;
}



}

//#endif
