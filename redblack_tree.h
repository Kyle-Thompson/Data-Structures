/*
 *
 */


#ifndef redblack_tree_h
#define redblack_tree_h
#include <memory>   // allocator

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
        enum Colour { RED, BLACK };

        value_type data;
        Colour colour;
        Node* parent;
        Node* left = nullptr;
        Node* right = nullptr;
        
        Node(const_ref element, Node* p) 
        : data(element)
        , parent(p)
        , colour(Colour.BLACK)
        {}
    };
   

/* Data members */
private:
    Node* _root = nullptr;
    size_type _size = 0;
    std::allocator<Node> alloc;
    auto compare = [](const_ref l, const_ref r){
        return l == r ? 0 : (l < r ? -1 : 1);
    }

/* Member functions */
public:
    /* Constructors */
    redblack_tree();
    redblack_tree(const redblack_tree<T>&);
    redblack_tree(redblack_tree<T>&&);
    redblack_tree(std::initializer_list<T>);
    ~redblack_tree();

    /* Assignmnent */
    redblack_tree<T>& operator=(const list<T, Alloc>&); 
    redblack_tree<T>& operator=(redblack_tree<T>&&); 
    redblack_tree<T>& operator=(std::initialiser_list<T>); 

    /* Capacity */
    bool empty() const;
    size_type size() const;

    /* Element access */
    bool has(const_ref) const;
    bool has(rvalue_ref) const;

    /* Modifiers */
    void push(const_ref);
    void push(rvalue_ref);
    template <class... Args>
        void emplace(Args&&...);
    void swap(redblack_tree<T>&);
    void clear(); noexcept;

    /* Operations */
    void remove(const_ref);
    void merge(redblack_tree<T>&);
    void merge(redblack_tree<T>&&);

};



// Constructors

/*
 Function: constructor
 Parameters:
  - 
  - 
 Return value: None

 Description:

 Complexity:
 */

// 1. default
template <class T>
redblack_tree<T>::redblack_tree()
{}

// 2. copy
template <class T>
redblack_tree<T>::redblack_tree(const redblack_tree<T>& rhs)
: _size(rhs._size)
, _root(rhs._root) // TODO currently shallow copy.
{}

// 3. move
template <class T>
redblack_tree<T>::redblack_tree(redblack_tree<T>&& rhs)
: _size(rhs._size)
, _root(rhs._root)
{}

// 4. initializer list
template <class T>
redblack_tree<T>::redblack_tree(std::initializer_list<T> il)
{}



// Assignment

/*
 Function: operator=
 */



// Capacity



// Element Access

/*
 
 */
template <class T>
bool
redblack_tree<T>::has(const_ref element)
{
    for (auto node = root; root;) {
        switch (compare(element, node.data)) {
        case -1:
            node = node.left;
            break;

        case 1:
            node = node.right;
            break;

        default:
            return true;
        }
    }

    return false;
}



template <class T>
bool
redblack_tree<T>::has(rvalue_ref element)
{
    for (auto node = root; root;) {
        switch (compare(element, node.data)) {
        case -1:
            node = node.left;
            break;

        case 1:
            node = node.right;
            break;

        default:
            return true;
        }
    }

    return false;
}




template <class T>
void
redblack_tree<T>::push(const_ref element)
{
    auto node = alloc.allocate(1);

    // If the tree is empty.
    if (!_root) {
        alloc.construct(node, element, nullptr);
        _root = node;
        return;
    }

    // Find the correct insertion spot.
    auto curr = _root;
    while (true) {
        switch (compare(element, curr.data)) {
        case -1:
            if (!curr.left) {
                alloc.construct(node, element, curr);
                curr.left = node;
            } else {
                curr = curr.left;
            }
            break;

        case 1:
            if (!curr.right) {
                alloc.construct(node, element, curr);
                curr.right = node;
            } else {
                curr = curr.right;
            }
            break;

        default:
            return;
        }
    }

    // Rotate. 
    
}


#endif
