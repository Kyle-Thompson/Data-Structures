/*

 */

template <class T>
class redblack_tree {

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
private:
    struct Node {
        bool colour; // true = red, false = black.
        
        pointer parent;
        pointer left_child;
        pointer right_child;

    };

/* Data members */
private:
    std::allocator<T> alloc;
    size_type size;
    size_type array_size;
    pointer elements;

/* Member functions */ 
public:
    redblack_tree();


    void add();
    
};
