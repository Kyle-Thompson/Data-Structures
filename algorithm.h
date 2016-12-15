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

namespace ads {

template <class T>
std::vector<T>&
sort(std::vector<T>& v) // sort(ads::container<T>& v)
{
    // TODO parallelize
    const auto size = v.size();

    auto print = [&]() {
        for (const T& i : v) {
            std::cout << i << ", ";
        }
        std::cout << "\n";
    };

    auto n_space_merge = [&](std::size_t index, std::size_t len) {
        std::vector<T> store;
        std::size_t end_range = (index+len < size ? len : size-index), mid = len/2;
        std::size_t l = index, r = index + mid;

        for (std::size_t i = 0; i < end_range; ++i) {
            if (l == index + mid) {
                store.push_back(v[r++]);
            } else if (r == index + end_range) {
                store.push_back(v[l++]);
            } else if (v[l] < v[r]) {
                store.push_back(v[l++]);
            } else {
                store.push_back(v[r++]);
            } 
        }

        for (std::size_t i = 0; i < end_range; ++i) {
            v[index + i] = store[i];
        }

        store.clear();
    };
    
    //auto const_space_merge = [&](std::size_t index, std::size_t len) {};


///*
print();
    for (std::size_t i = 1; i < size;) {
        i *= 2;
        for (std::size_t j = 0; j < size; j += i) {
            n_space_merge(j, i);
        }
    }
print();
//*/
/*
    print();
    //n_space_merge(0, 2); print();
    //n_space_merge(2, 2); print();
    n_space_merge(4, 2); print();
    n_space_merge(6, 2); print();
    //n_space_merge(0, 4); print();
    n_space_merge(4, 4); print();
    //n_space_merge(0, 8); print();
*/
    return v;
}



}

//#endif
