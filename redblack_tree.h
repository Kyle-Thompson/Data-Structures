/*
 *
 */


#ifndef redblack_tree_h
#define redblack_tree_h


#include <memory>   // allocator
#include <stdio.h>

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
        
        Node(const_ref el, Node* p, Colour c=Colour::RED) 
        : data(el)
        , colour(c)
        , parent(p)
        {}

/*
        void push_black() {
            colour = Colour::RED;
            if (left) left->colour = Colour::BLACK;
            if (right) right->colour = Colour::BLACK;
        }
        
        void pull_black() {
            colour = Colour::BLACK;
            if (left) left->colour = Colour::RED;
            if (right) right->colour = Colour::RED;
        }

        void flip_left() {
            std::swap(colour, right->colour);
            rotate_left();
        }

        void flip_right() {
            std::swap(colour, left->colour);
            rotate_right();
        }
*/

    };
   

/* Data members */
private:
    Node* _root = nullptr;
    size_type _size = 0;
    std::allocator<Node> alloc;
    std::function<int(const_ref, const_ref)> compare = [](const_ref l, const_ref r){
        return l == r ? 0 : (l < r ? -1 : 1);
    };

/* Member functions */
public:
    /* Constructors */
    redblack_tree() = default;
    redblack_tree(const redblack_tree<T>&);
    redblack_tree(redblack_tree<T>&&);
    redblack_tree(std::initializer_list<T>);
    ~redblack_tree() = default;

    /* Assignmnent */
    redblack_tree<T>& operator=(const redblack_tree<T>&); 
    redblack_tree<T>& operator=(redblack_tree<T>&&); 
    redblack_tree<T>& operator=(std::initializer_list<T>); 

    /* Capacity */
    bool empty() const;
    size_type size() const;

    /* Element access */
    bool has(const_ref) const;
    bool has(rvalue_ref) const;

    /* Modifiers */
    void push(const_ref);
    //void push(rvalue_ref);
    template <class... Args>
        void emplace(Args&&...);
    void swap(redblack_tree<T>&);
    void clear() noexcept;

    /* Operations */
    void remove(const_ref);
    void merge(redblack_tree<T>&);
    void merge(redblack_tree<T>&&);

/* Helper functions */
private:
    pointer find(const_ref);
    pointer find(rvalue_ref);

    Node* uncle(Node*);
    Node* grandparent(Node*);
    
    void rotate_left(Node*);
    void rotate_right(Node*);

    void insert_case1(Node*);
    void insert_case2(Node*);
    void insert_case3(Node*);
    void insert_case4(Node*);
    void insert_case5(Node*);

public:    
    void print();
};


#include <iostream>
template <class T>
void
redblack_tree<T>::print() {
    std::function<void (Node*, size_type)> helper = [&](Node* n, size_type count) {
        for (size_type i = 0; i < count; ++i) std::cout << "| ";
        std::cout << n->data << "\n";
        //std::cout << "data is " << n->data << ". count is " << count << '\n';
        //std::cout << "left is null? " << (n->left == nullptr) << ". right is null? " << (n->right == nullptr) << "\n\n";
        
        if (n->left) helper(n->left, count+1);

        if (n->right) helper(n->right, count+1);
    };

    if (_root) helper(_root, 0);
}

template <class T>
bool
redblack_tree<T>::has(const_ref element) const
{
    for (auto node = _root; _root;) {
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
redblack_tree<T>::has(rvalue_ref element) const
{
    for (auto node = _root; node;) {
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
        alloc.construct(node, element, nullptr, Node::Colour::BLACK);
        _root = node;
        return;
    }

    // Find the correct insertion spot.
    auto curr = _root;
    bool added = false;
    while (!added) {
        switch (compare(element, curr->data)) {
        case -1:
            if (!curr->left) {
                alloc.construct(node, element, curr);
                curr->left = node;
                curr = curr->left;
                added = true;
                break;
            } else {
                curr = curr->left;
            }
            break;

        case 1:
            if (!curr->right) {
                alloc.construct(node, element, curr);
                curr->right = node;
                curr = curr->right;
                added = true;
                break;
            } else {
                curr = curr->right;
            }
            break;

        default:
            return;
        }
    }

    insert_case2(curr);
    
}



// Helper functions

template <class T>
typename redblack_tree<T>::Node* 
redblack_tree<T>::grandparent(Node* n) {
    return (n->parent != nullptr ? n->parent->parent : nullptr);
}

template <class T>
typename redblack_tree<T>::Node* 
redblack_tree<T>::uncle(Node* n) {
    Node* g = grandparent(n);
    if (g == nullptr) return nullptr;
    return (n->parent == g->left ? g->right : g->left);
}

template <class T>
void 
redblack_tree<T>::rotate_left(Node* n) {
    printf("Rotating left");
    n->right->parent = n->parent;
    if (n->parent) {
        if (n == n->parent->left) {
            n->parent->left = n->right;
        } else {
            n->parent->right = n->right;
        }
    }
    n->parent = n->right;
    n->right = n->parent->left;
    n->right->parent = n;
    n->parent->left = n;
}

template <class T>
void 
redblack_tree<T>::rotate_right(Node* n) {
    printf("Rotating right");
    n->left->parent = n->parent;
    if (n->parent) {
        if (n == n->parent->left) {
            n->parent->left = n->left;
        } else {
            n->parent->right = n->left;
        }
    }
    n->parent = n->left;
    n->left = n->parent->right;
    n->left->parent = n;
    n->parent->right = n;
}

template <class T>
void redblack_tree<T>::insert_case1(Node* n) {
    printf("Inside insert case 1\n");
    if (n->parent == nullptr) {
        n->colour = Node::Colour::BLACK;
    } else {
        insert_case2(n);
    }
}

template <class T>
void redblack_tree<T>::insert_case2(Node* n) {
    printf("Inside insert case 2\n");
    if (n->parent->colour == Node::Colour::BLACK) {
        return;
    } else {
        insert_case3(n);
    }
}

template <class T>
void redblack_tree<T>::insert_case3(Node* n) {
    printf("Inside insert case 3\n");
    Node* u = uncle(n);
    if (u != nullptr && u->colour == Node::Colour::RED) {
        n->parent->colour = Node::Colour::BLACK;
        u->colour = Node::Colour::BLACK;
        Node* g = grandparent(n);
        g->colour = Node::Colour::RED;
        insert_case1(n);
    } else {
        insert_case4(n);
    }
}

template <class T>
void redblack_tree<T>::insert_case4(Node* n) {
    printf("Inside insert case 4\n");
    Node* g = grandparent(n);
    if (n == n->parent->right && n->parent == g->left) {
        rotate_left(n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == g->right) {
        rotate_right(n->parent);
        n = n->right;
    }
    insert_case5(n);
}

template <class T>
void redblack_tree<T>::insert_case5(Node* n) {
    printf("Inside insert case 5\n");
    Node* g = grandparent(n);
    n->parent->colour = Node::Colour::BLACK;
    g->colour = Node::Colour::RED;
    if (n == n->parent->left) {
        rotate_right(g);
    } else {
        rotate_left(g);
    }
}


#endif
