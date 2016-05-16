/*
 File:   stack.h
 Author: Kyle Thompson
 
 Purpose:
 A stack using an arbitrary backing store.
 
 Implementation:
 
 
 TODO:
 - Separate function implementations from class definition.
 - Fill in implementation ^^^.
 */


#ifndef stack_h
#define stack_h

#include "list.h"

template <class T, class C = list<T, Alloc>>
class stack {
    

/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef C           container_type;
    typedef T&          reference;
    typedef const T&    const_ref;
    
/* Member functions */
public:
    /* Capacity */
    size_type size() {
        return _container.size();
    }
    
    /* Element access */
    reference top() {
        return _container.last();
    }
    
    /* Modifiers */
    void push(const_ref element) {
        _container.push_back(element);
    }
    
    void pop() {
        _container.pop_back();
    }
    
    void clear() {
        _container.clear();
    }
    

    
private:
    container_type _container;
    
};

#endif /* stack_h */
