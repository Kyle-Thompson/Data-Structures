/*
 preamble.
 */


#ifndef binary_tree_h
#define binary_tree_h

#include "tree.h"

template <class T>
class binary_tree : public tree {
    
protected:
    class Node : public tree::node {
        
    public:
        std::pair<Node*, Node*> children;
    };
    
    
public:
    virtual void merge(binary_tree<T>&) = 0;
    virtual void merge(binary_tree<T>&&) = 0;
    
};

#endif /* binary_tree_h */
