/*
 preamble.
 */


#ifndef Tree_h
#define Tree_h

#include <memory>

template <class T>
class tree {
    
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
    class Node {
        
    public:
        Node* parent;
        T data;
    };
    

/* Data members */
protected:
    Node* _root = nullptr;
    size_type _size = 0;
    std::allocator<T> alloc;
    
    
/* Member functions */
public:
    size_type size();
    bool empty();
    
};



// Capacity

/*
 
 */
template <class T>
inline typename tree<T>::size_type
tree<T>::size()
{
    return _size;
}


/*
 
 */
template <class T>
inline bool
tree<T>::empty()
{
    return _size == 0;
}

#endif /* Tree_h */
