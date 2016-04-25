#ifndef stack_h
#define stack_h

#include "LinkedList.h"

template <class T, class C = LinkedList<T>>
class stack {
    

/* Type Definitions */
public:
    typedef std::size_t size_type;
    typedef C           container_type;
    typedef T&          reference;
    typedef const T&    const_ref;
    
public:
    void push(const_ref element) {
        _container.push_back(element);
    }
    
    void pop() {
        _container.pop_back();
    }
    
    reference top() {
        return _container.last();
    }
    
    void clear() {
        _container.clear();
    }
    
    size_type size() {
        return _container.size();
    }
    
private:
    container_type _container;
    
};

#endif /* stack_h */
