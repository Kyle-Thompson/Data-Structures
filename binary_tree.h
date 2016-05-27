/*
 preamble.
 */


#ifndef binary_tree_h
#define binary_tree_h

#include "tree.h"

template <class T>
class binary_tree : public tree<T> {
    
/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_ptr;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;
    
    
protected:
    class Node : public tree<T>::Node {
        
    public:
        std::pair<Node*, Node*> children = std::make_pair(nullptr, nullptr);
    };
    
    
/* Member functions */
public:
    virtual void add(const_ref) = 0;
    virtual void remove(const_ref) = 0;
    virtual void merge(binary_tree<T>&) = 0;
    virtual void merge(binary_tree<T>&&) = 0;
    
};

#endif /* binary_tree_h */
