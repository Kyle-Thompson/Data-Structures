/*

 */

#include <memory>      // allocator
#include <utility>     // swap
#include <math.h>      // log2

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
        bool sentinel;
        size_type index;
        size_type depth;
        pointer data;

        Node()
        : sentinel(true)
        , index((this-elements)/sizeof(Node)) // this could be so wrong.
        , colour(false)
        {}

        Node(const_ref element)
        : data(&element)
        , sentinel(false)
        , index((this-elements)/sizeof(Node)) // this could be so wrong.
        , colour(true)
        {
            // check if this node is on the bottom row.
            if (log2(index) == log2(array_size))
                resize();

            // create sentinel nodes
            alloc.construct(left);
            alloc.construct(right);

            /*Node::*/insert(this);
/*
            // root check
            if (index == 0) {
                colour = false;
                return;
            }

            // If parent node is black, nothing to do.
            if (!parent()->colour)
                return;

            if (uncle()->colour) */
        }

        static void insert(Node*);
        void rotate_right();
        void rotate_left();
        size_type parent_index() { return (index - 2+index%2)/2; }
        size_type left_index() { return 2*index+1; }
        size_type right_index() { return 2*index+2; }
        Node* parent() { return &elements[(index - 2+index%2)/2]; }
        Node* sibling() { return &elements[index + 1 - 2*(index%2)]; }
        Node* uncle() { return parent()->sibling(); }
        Node* left() { return &elements[2*index+1]; }  // TODO: bounds check
        Node* right() { return &elements[2*index+2]; } // ditto
        // to calculate depth: log2(index+1)

    };

/* Data members */
private:
    std::allocator<Node> alloc;
    size_type size;
    size_type array_size;
    Node* elements;

/* Member functions */ 
public:
    redblack_tree(size_type=15);

    void add(const_ref);
    void remove(const_ref);
    void find(const_ref);

/* Utility functions */
private:
    void resize();
};


template <class T>
redblack_tree<T>::redblack_tree(size_type initial_size)
: size(0)
, array_size(initial_size)
, elements(alloc.allocate(initial_size))
{
    alloc.construct(elements);
}


template <class T>
redblack_tree<T>::add(const_ref element)
{
    size_type index = 0;
    while (!elements[index].sentinel)
        index = index * 2 + 1 + (elements[index] < element);

    alloc.construct(elements+index, element);
}
