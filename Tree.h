#ifndef Tree_h
#define Tree_h

template <class T>
class Tree {
    
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
    };
    

/* Member functions */
public:
    virtual void add(const_ref) = 0;
    virtual void remove(const_ref) = 0;
};

#endif /* Tree_h */
