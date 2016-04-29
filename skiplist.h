/*
 File:   skiplist.h
 Author: Kyle Thompson
 
 
 TODO:
  - Replace std::vector with custom vector when vector is written.
  - Organize.
 */

#ifndef skiplist_h
#define skiplist_h

#include <vector> // temporary

template <class T>
class skiplist {

/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;

    
/* Node definition */
private:
    class Node {
        
    public:
        std::vector<Node> next;
        size_type height;
        T data;
        
        Node()
            : height(2)
            , next({nullptr, nullptr})
        {}
        
        Node(Node* rhs)
        
        Node(const_ref element)
            : data(element)
            , height(get_height())
        {}
        
        size_type get_height()
        {
            return 2; // Temporary
        }
    };

    
/* Data members */
private:
    Node* _start;
    Node* _end;
    size_type _height;
    
    
/* Member functions */
public:
    skiplist();
    const_ref get(size_type);
    void set(size_type, const_ref);
    void add(size_type, const_ref);
    void remove(size_type);
};



// Constructors

/*
 
 */
template <class T>
skiplist<T>::skiplist()
{
    _end = new Node();
    _start = new Node(_end);
    _height = 2;
}



































#endif /* skiplist_h */
