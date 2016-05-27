/*
 preamble.
 */


#ifndef search_tree_h
#define search_tree_h

#include "binary_tree.h"

template <class T>
class search_tree : public binary_tree<T> {
    
/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_ptr;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;
    
    
/* Node definition */
protected:
    class Node : public binary_tree<T>::Node {
        
    public:
        Node(const_ref, Node*);
    };
    
    
/* Member functions */
public:
    /* Constructors */
    search_tree();
    search_tree(const search_tree<T>&);
    search_tree(search_tree<T>&&);
    // iterator constructor here at some point
    search_tree(std::initializer_list<T>);
    //~search_tree();
    
    /* Assignment */
    search_tree<T>& operator=(const search_tree<T>&);
    search_tree<T>& operator=(search_tree<T>&&);
    search_tree<T>& operator=(std::initializer_list<T>);
    
    /* Element access */
    virtual void add(const_ref);
    virtual void remove(const_ref);
    
    /* Modifiers */
    virtual void merge(binary_tree<T>&);
    virtual void merge(binary_tree<T>&&);
    
    
    /* Operations */
    
    
};



// Node

/*
 
 */
template <class T>
search_tree<T>::Node::Node(const_ref element, Node* parent)
: binary_tree<T>::Node(element, parent)
{}



// Constructor

template <class T>
search_tree<T>::search_tree()
{}



// Element Access

/*
 
 */
template <class T>
void
search_tree<T>::add(const_ref)
{
    
}


/*
 
 */
template <class T>
void
search_tree<T>::remove(const_ref)
{
    
}


// Modifiers

/*
 
 */
template <class T>
void
search_tree<T>::merge(binary_tree<T>& other_tree)
{
    
}


/*
 
 */
template <class T>
void
search_tree<T>::merge(binary_tree<T>&& other_tree)
{
    
}



// Operations




#endif /* search_tree_h */
