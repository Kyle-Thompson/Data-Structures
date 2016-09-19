//#ifndef ALGORITHM_H
//#define ALGORITHM_H

/*
 * Functions:
 *    sort
 * 
 */

// delete all these includes later.
#include <vector>
#include <iostream>


#include <algorithm>
#include "typedefs.h"

namespace ads {

template <class T>
std::vector<T>&
sort(std::vector<T>& v) // sort(ads::container<T>& v)
{
    // TODO parallelize
    const auto size = v.size();

    //auto print = [&](std)

    auto n_space_merge = [&](size_type index, size_type len) {
        T store[1000]; // TODO delete when using only constant extra space.
        size_type end = std::min(index + len, size), mid = len/2;
        
        size_type l = index, r = index + mid;
        for (size_type i = 0; i < end; ++i) {
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

        for (size_type i = 0; i < end; ++i)
            v[index + i] = store[i];
    };
    
    auto const_space_merge = [&](size_type index, size_type len) {

    }

//    for (size_type i = 1; i < size;) {
//        i *= 2;
//        for (size_type j = 0; j < size + i /* unsure about this */; j += i) {
//            merge(j, i);
//        }
//    }

    n_space_merge(2, 2);
    return v;
}



}

//#endif
