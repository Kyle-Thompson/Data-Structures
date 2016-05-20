/*
 File:   list.h
 Author: Kyle Thompson
 
 Purpose:
    This class is meant to be a fully standard compliant linked list which will act as a
    foundation for more linked list based data structures.
 
 Implementation:
  - A custom bidirectional iterator is implemented for accessing and iterating through the
    elements. 
  - A single dummy node is used to simplify insertion and deletion operations as well as 
    iterator functions like end() and rbegin().
 
 TODO:
  - Find out how to correctly use an allocator and use it.
  - Test all functions.
  - Find out if there's a viable way to make insert and erase take a const iterator.
  - Make sure that elements being inserted by range aren't still references to one another.
  - Test with valgrind for memory leaks. Like for real. Who knows what's happened with these
    allocators now.
  - Find a good category for operator=.
  - Find how to correctly implement const_iterator.
  - Update comments of similar functions (all different kinds of merge and such) to only be 
    one descriptor comment.
  - Find out what merge(&&, comp) needs different from merge(&, comp). (Also insert& and &&)
  - Find out if iterator -> should return a pointer or reference.
  - See how much code can be moved from derived iterators to list_iterator.
  - Make list_iterator abstract.
  - Find out why this works with clang but not g++.
  - Find out how the current use of allocators actually works.
  - Consider node heirarchy with node inheriting from dummy node.
  - Find a better way to do push_front than the horrible hacky way it is now.
  - Make splice(pos, list) constant.
  - See if it's possible to remove the need for the self check in move_before.
 */


#ifndef list_h
#define list_h

#include <algorithm>   // move
#include <cassert>     // assert
#include <cstddef>     // ptrdiff_t
#include <functional>  // function
#include <iterator>    // iterator
#include <memory>      // allocator
#include <utility>     // swap

template <class T, class Alloc = std::allocator<T>>
class list {
    
/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          pointer;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;


/* Node definition */
private:
    class Node {
        
    public:
        Node* prev;
        Node* next;
        T data;
        
        Node();                   // Dummy node constructor
        Node(const_ref, Node*);   // Data node constructor
        Node(rvalue_ref, Node*);  // Data node constructor
        
        void detach();
        void move_before(Node*);
        void insert_before(Node*);
        
        static Node* create_dummy();
        static Node* create_node(const_ref, Node*);
        static Node* create_node(rvalue_ref, Node*);
        static void  delete_node(Node*);
    };
    
//    class dummy_node : public Node {
//    public:
//        dummy_node();
//    };
//    
//    class data_node : public Node {
//    public:
//        using Node::next;
//        using Node::prev;
//        T data;
//        
//        data_node(const_ref, Node*);
//        data_node(rvalue_ref, Node*);
//        
//        void detach();
//        void move_before(Node*);
//        void insert_before(Node*);
//    };

    
/* Iterators */
public:
    class list_iterator {
        
    /* Iterator data members */
    protected:
        Node* node;
        
    public:
        list_iterator(Node* n) : node(n) {}
        bool operator==(const list_iterator& rhs) { return node->data == rhs.node->data; }
        bool operator!=(const list_iterator& rhs) { return !(*this == rhs); }
    };
    
    
    class iterator : public list_iterator {
    
        friend class list<T, Alloc>;
        
    private:
        using list_iterator::node;
        
    /* Iterator member functions */
    public:
        iterator(Node* n) : list_iterator(n) {}
        reference operator*()  { return node->data; }
        reference operator->() { return node->data; }
        iterator& operator++() { node = node->next; return *this; }
        iterator operator++(int) { iterator temp(*this); node = node->next; return temp; }
        iterator& operator--() { node = node->prev; return *this; }
        iterator operator--(int) { iterator temp(*this); node = node->prev; return temp; }
        iterator next() { return iterator(node->next); }
        iterator prev() { return iterator(node->prev); }
    };
    
    
    class const_iterator : public list_iterator {
        
        friend class list<T, Alloc>;
        
    private:
        using list_iterator::node;
        
    /* Iterator member functions */
    public:
        const_iterator(Node* n) : list_iterator(n) {}
        const_ref operator*()  { return node->data; }
        const_ref operator->() { return node->data; }
        const_iterator& operator++() { node = node->next; return *this; }
        const_iterator operator++(int) { const_iterator temp(*this); node = node->next; return temp; }
        const_iterator& operator--() { node = node->prev; return *this; }
        const_iterator operator--(int) { const_iterator temp(*this); node = node->prev; return temp; }
        const_iterator next() { return const_iterator(node->next); }
        const_iterator prev() { return const_iterator(node->prev); }
    };
    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    

/* Data members */
private:
    Node* _dummy;          // Dummy node between start and end of list.
    size_type _size = 0;   // Number of real elements in list.
    
    
/* Member functions */
public:
    /* Constructors */
    list();
    list(size_type, const_ref);
    list(iterator, iterator);                                                    // Not yet implemented.
    list(const list<T, Alloc>&);
    list(list<T, Alloc>&&);                                                       // Not yet implemented.
    list(std::initializer_list<T>);
    ~list();
    
    // where to even put this assignment operator?
    //list<T, Alloc>& operator=(list<T, Alloc>&);                                           // Not yet implemented.
    //list<T, Alloc>& operator=(list<T, Alloc>&&);                                           // Not yet implemented.
    
    /* Iterators */
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    
    /* Capacity */
    bool empty() const;
    size_type size() const;
    
    /* Element access */
    reference front() const;
    reference last() const;
    reference at(size_type) const;
    reference operator[](size_type) const;
    
    /* Modifiers */
    void assign(iterator, iterator);                                                   // Not yet implemented.
    void assign(size_type, const_ref);                                                 // Not yet implemented.
    void assign(std::initializer_list<value_type>);                                    // Not yet implemented.
    void push_front(const_ref);
    void push_front(rvalue_ref);
    void push_back(const_ref);
    void push_back(rvalue_ref);
    template <class... Args>
        void emplace_front(Args&&...);                                                 // Not yet implemented.
    template <class... Args>
        void emplace_back(Args&&...);                                                  // Not yet implemented.
    template <class... Args>
        iterator emplace(const_iterator position, Args&&...);                          // Not yet implemented.
    void pop_front();
    void pop_back();
    iterator insert(iterator, const_ref);
    iterator insert(iterator, size_type, const_ref);
    iterator insert(iterator, iterator, iterator);
    iterator insert(iterator, rvalue_ref);
    iterator insert(iterator, std::initializer_list<value_type>);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void swap(list<T, Alloc>&);                                                               // Unknown if working.
    void clear() noexcept;
    
    /* Operations */
    void splice(const_iterator, list<T, Alloc>&);                                             // Not yet implemented.
    void splice(const_iterator, list<T, Alloc>&&);                                            // Not yet implemented.
    void splice(const_iterator, list<T, Alloc>&, const_iterator);                             // Not yet implemented.
    void splice(const_iterator, list<T, Alloc>&&, const_iterator);                            // Not yet implemented.
    void splice(const_iterator, list<T, Alloc>&, const_iterator, const_iterator);             // Not yet implemented.
    void splice(const_iterator, list<T, Alloc>&&, const_iterator, const_iterator);            // Not yet implemented.
    void remove(const_ref);
    template <class Predicate>
        void remove_if(Predicate);
    void unique();
    template <class BinaryPredicate>
        void unique(BinaryPredicate);
    void merge(list<T, Alloc>&);                                                              // Not yet implemented.
    void merge(list<T, Alloc>&&);                                                             // Not yet implemented.
    template <class Compare>
        void merge(list<T, Alloc>&, Compare);                                                 // Not yet implemented.
    template <class Compare>
        void merge(list<T, Alloc>&&, Compare);                                                // Not yet implemented.
    void sort();
    template <class Compare>
        void sort(Compare);
    void reverse() noexcept;
    
};



// Node

/*
 Function: Node Constructor
 Parameters:
  - element: The data that the node stores.
  - next_node: The node which will be after this node.
 */
template <class T, class Alloc>
list<T, Alloc>::Node::Node()
    : prev(this)
    , next(this)
{}


template <class T, class Alloc>
list<T, Alloc>::Node::Node(const_ref element, Node* next_node)
    : data(element)
{
    insert_before(next_node);
}

template <class T, class Alloc>
list<T, Alloc>::Node::Node(rvalue_ref element, Node* next_node)
    : data(std::move(element))
{
    insert_before(next_node);
}


/*
 Function: unhook
 */
template <class T, class Alloc>
void
list<T, Alloc>::Node::detach()
{
    next->prev = this->prev;
    prev->next = this->next;
    
    next = prev = nullptr;
}


/*
 Function: insert_before
 Parameters:
 - other_node: The node which this node will be moved in
               front of.
 Return value: None
 
 Description:
    Takes a detached node and inserts it in front of another
    node.
 */
template <class T, class Alloc>
void
list<T, Alloc>::Node::insert_before(Node* next_node)
{
    next = next_node;
    prev = next_node->prev;
    
    next_node->prev->next = this;
    next_node->prev = this;
}


/*
 Function: move_before
 Parameters:
  - other_node: The node which this node will be moved in 
                front of.
 Return value: None
 
 Description: 
    Moves this node (which is currently in this list)
    infront of another node in a potentially different list.
 
 Complexity: Constant
 */
template <class T, class Alloc>
void
list<T, Alloc>::Node::move_before(Node* next_node)
{
    if (this == next_node)
        return;
    
    detach();
    insert_before(next_node);
}


/*
 Function: create dummy
 Parameters: None
 Return value: Node*
 */
template <class T, class Alloc>
typename list<T, Alloc>::Node*
list<T, Alloc>::Node::create_dummy()
{
    typename Alloc::template rebind<Node>::other alloc;
    auto node = alloc.allocate(1);
    alloc.construct(node);
    
    return node;
}


/*
 
 */
template <class T, class Alloc>
typename list<T, Alloc>::Node*
list<T, Alloc>::Node::create_node(const_ref element, Node* next_node)
{
    typename Alloc::template rebind<Node>::other alloc;
    auto node = alloc.allocate(1);
    alloc.construct(node, element, next_node);
    
    return node;
}


/*
 
 */
template <class T, class Alloc>
typename list<T, Alloc>::Node*
list<T, Alloc>::Node::create_node(rvalue_ref element, Node* next_node)
{
    typename Alloc::template rebind<Node>::other alloc;
    auto node = alloc.allocate(1);
    alloc.construct(node, std::move(element), next_node);
    
    return node;
}


/*
 
 */
template <class T, class Alloc>
void
list<T, Alloc>::Node::delete_node(Node* node)
{
    typename Alloc::template rebind<Node>::other alloc;
    alloc.destroy(node);
    alloc.deallocate(node, 1);
}


// Constructors

/*
 Function: default constructor
 Parameters: None
 Return value: None
 
 Description:
    Initializes a default, empty linked list.
 */
template <class T, class Alloc>
list<T, Alloc>::list()
: _dummy(Node::create_dummy())
{}


/*
 Function: fill constructor
 Parameters:
  - n: The number of times the element will be copied
       into the list.
  - element: The element used to fill the list.
 Return value: None
 
 Description:
    Initializes a list with n copies of element.
 */
template <class T, class Alloc>
list<T, Alloc>::list(size_type n, const_ref element)
    : _dummy(Node::create_dummy())
{
    insert(end(), n, element);
}


/*
 Function: range constructor.
 */
template <class T, class Alloc>
list<T, Alloc>::list(iterator, iterator)
    : _dummy(Node::create_dummy())
{}


/*
 Function: copy constructor
 Parameters: 
  - rhs: Reference to other list being copied from.
 Return value: None
 
 Description:
    Initializes a linked list as a deep copy of another
    linked list.
 */
template <class T, class Alloc>
list<T, Alloc>::list(const list<T, Alloc>& rhs)
    : _dummy(Node::create_dummy())
{
    insert(end(), rhs.begin(), rhs.end());
}


/*
 Function: move constructor.
 */
template <class T, class Alloc>
list<T, Alloc>::list(list<T, Alloc>&&)
    : _dummy(Node::create_dummy())
{}


/*
 Function: initializer list constructor
 Parameters:
  - il: An initializer list of elements to construct the
        list with.
 Return value: None
 
 Description:
    Initializes a list based on an initializer list.
 */
template <class T, class Alloc>
list<T, Alloc>::list(std::initializer_list<T> il)
    : _dummy(Node::create_dummy())
{
    insert(end(), il);
}


/*
 Function: Destructor
 Parameters: None
 Return value: None
 
 Description:
    Clears all nodes and associated data within the linked list.
 */
template <class T, class Alloc>
list<T, Alloc>::~list()
{
    clear();
    Node::delete_node(_dummy);
}



// Iterator

/*
 Function: begin
 Parameters: None
 Return value: An iterator to the first position in the list.
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::begin() const
{
    return _dummy->next;
}


/*
 Function: end
 Parameters: None
 Return value: An iterator to the past-the-end position in the list.
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::end() const
{
    return _dummy;
}


/*
 Function: cbegin
 Parameters: None
 Return value: A const iterator to the first position in the list.
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::const_iterator
list<T, Alloc>::cbegin() const
{
    assert(!empty());
    return const_iterator(_dummy->next);
}


/*
 Function: cend
 Parameters: None
 Return value: A const iterator to the past-the-end position in the list.
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::const_iterator
list<T, Alloc>::cend() const
{
    return const_iterator(_dummy);
}


/*
 Function: rbegin
 Parameters: None
 Return value: A reverse iterator to the first position in the reversed
               list. (Last element in the real list.)
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::reverse_iterator
list<T, Alloc>::rbegin() const
{
    return _dummy->prev;
}


/*
 Function: rend
 Parameters: None
 Return value: A reverse iterator to the past-the end position in the 
               reversed list. (One before first position in real list.)
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::reverse_iterator
list<T, Alloc>::rend() const
{
    return _dummy;
}


/*
 Function: crbegin
 Parameters: None
 Return value: An const reverse iterator to the first position in the 
               reversed list. (Last element in the real list.)
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::const_reverse_iterator
list<T, Alloc>::crbegin() const
{
    return _dummy->prev;
}


/*
 Function: crend
 Parameters: None
 Return value: A const reverse iterator to the past-the-end position in 
               the reversed list. (One before first position in real list.)
 */
template <class T, class Alloc>
inline typename list<T, Alloc>::const_reverse_iterator
list<T, Alloc>::crend() const
{
    return _dummy;
}



// Capacity

/*
 Function: empty
 Parameters: None
 Return value: Whether or not the list is empty.
 */
template <class T, class Alloc>
inline bool
list<T, Alloc>::empty() const
{
    return _size == 0;
}


/*
 Function: size
 Parameters: None
 Return value: The size of the list.
 */
template <class T, class Alloc>
inline std::size_t
list<T, Alloc>::size() const
{
    return _size;
}


// Element access

/*
 Function: front
 Parameters: None
 Return value: A reference to the first element in the list.
 */
template <class T, class Alloc>
inline T&
list<T, Alloc>::front() const
{
    assert(!empty());
    return _dummy->next->data;
}


/*
 Function: last
 Parameters: None
 Return value: A reference to the last element in the list.
 */
template <class T, class Alloc>
inline T&
list<T, Alloc>::last() const
{
    assert(!empty());
    return _dummy->prev->data;
}


/*
 Function: at
 Parameters:
  - index: The position within the list to access.
 Return value: A reference to the index-th position in the list.
 */
template <class T, class Alloc>
T&
list<T, Alloc>::at(size_type index) const
{
    assert (index < _size);
    
    auto node = _dummy->next;
    while (index-- > 0)
        node = node->next;
    
    return node->data;
}


/*
 Function: operator[]
 Parameters:
  - index: The position within the list to access.
 Return value: A reference to the index-th position in the list.
 */
template <class T, class Alloc>
inline T&
list<T, Alloc>::operator[](size_type index) const
{
    return at(index);
}


// Modifiers


//void assign(iterator, iterator);                                                   // Not yet implemented.
//void assign(size_type, const_ref);                                                 // Not yet implemented.
//void assign(std::initializer_list<T, Alloc>);                                             // Not yet implemented.



/*
 Function: push_front
 Parameters:
  - element: A const reference to the element being added to the list.
 Return value: None
 
 Description:
    Adds a given element into the front of the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::push_front(const T& element)
{
    if (!empty())
        insert(begin(), element);
    else
        insert(begin(), element);
}


/*
 Function: push_front
 Parameters:
  - element: An r-value reference to the element being added to the
             list.
 Return value: None
 
 Description:
    Adds a given element into the front of the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::push_front(T&& element)
{
    if (!empty())
        insert(begin(), std::move(element));
    else
        insert(end(), std::move(element));
}


/*
 Function: push_back
 Parameters:
  - element: A const reference to the element being added to the list.
 Return value: None
 
 Description:
    Adds a given element into the back of the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::push_back(const T& element)
{
    insert(end(), element);
}


/*
 Function: push_back
 Parameters:
  - element: An r-value reference to the element being added to the
             list.
 Return value: None
 
 Description:
    Adds a given element into the back of the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::push_back(T&& element)
{
    insert(end(), std::move(element));
}


/*
 Function: emplace_front
 Parameters:
  - args: Arguments used to construct the new T object.
 Return value: None
 
 Description:
    Creates a new T object and adds it to the front of the list.
 
 Complexity: O(T(args)) -> Complexity of T(args) constructor.
 */
template <class T, class Alloc>
template <class... Args>
void
list<T, Alloc>::emplace_front(Args&&... args)
{
    // TODO: Fill in function definition.
    // Likely needs an allocator to work.
}


/*
 Function: emplace_back
 Parameters:
 - args: Arguments used to construct the new T object.
 Return value: None
 
 Description:
    Creates a new T object and adds it to the back of the list.
 
 Complexity: O(T(args)) -> Complexity of T(args) constructor.
 */
template <class T, class Alloc>
template <class... Args>
void
list<T, Alloc>::emplace_back(Args&&... args)
{
    // TODO: Fill in function definition.
}


/*
 Function: pop_front
 Parameters: None
 Return value: None
 
 Description:
    Removes the first element in the list from the list and returns it.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::pop_front()
{
    erase(begin());
}


/*
 Function: pop_back
 Parameters: None
 Return value: None
 
 Description:
    Removes the first element in the list from the list and returns it.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::pop_back()
{
    //erase(iterator(_dummy->prev));
    erase(--end());
}


/*
 Function: insert
 Parameters:
  - pos: An iterator at the positition which the new element will be
         inserted in front of.
  - element: The new item to be inserted.
 Return value: An iterator pointing to the newly inserted element.
 
 Description:
    Inserts an element into the list at a given position indicated by 
    the pos iterator.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator pos, const_ref element)
{
    auto node = Node::create_node(element, pos.node);
    
    node->prev->next = node;
    node->next->prev = node;
    
    ++_size;
    
    return iterator(node);
}


/*
 Function: insert
 Parameters:
  - pos: An iterator at the position which the new elements will be
         inserted in front of.
  - n: The number of duplicate elements to be inserted.
  - element: The element to be inserted n times.
 Return value: An iterator to the first element in the group of newly
               inserted elements.
 
 Description:
    Adds an element n times into the list at a given position.
 
 Complexity: O(n) -> Linear in number of elements to be inserted.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator pos, size_type n, const_ref element)
{
    while (--n > 0)
        insert(pos, element);
    
    return insert(pos, element);
}


/*
 Function: insert
 Parameters:
  - pos: An iterator at the position which the new elements will be
         inserted in front of.
  - first: The first element in the range of elements to be copied.
  - last: The last element in the range of elements to be copied and
          inserted. This element is not included in the insertion.
 Return value: An iterator to the first element in the range of newly 
               inserted elements.
 
 Description:
    Copies elements [first, last) into the list at a given position.
 
 Complexity: O(dist(first, last)) -> Linear in the number of elements
                                     between first and last.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator pos, iterator first, iterator last)
{
    while (first != last)
        insert(pos, *first++);
    
    return pos;
}

/*
 Function: insert
 Parameters:
  - pos: An iterator at the position which the new element will be
         inserted in front of.
  - element: The new item to be inserted.
 
 Description:
    Inserts an element into the list at a given position indicated by
    the pos iterator.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator pos, rvalue_ref element)
{
    return insert(pos, element);
}


/*
 Function: insert
 Parameters:
  - pos: An iterator at the position which the new element will be
         inserted in front of.
  - il: An initializer list of new values to be added to the list.
 
 Description:
    Adds all the items in an initializer list to the list at a given 
    position.
 
 Complexity: O(|il|) -> Linear in the size of the initializer list.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator pos, std::initializer_list<T> il)
{
    for (auto it : il)
        insert(pos, it);
    
    return --pos;
}


/*
 Function: erase
 Parameters:
  - pos: An iterator pointing to the element to be removed.
 Return value: An iterator pointing to the element that followed the one 
               just removed.
 
 Description:
    Removes the element at position pos from the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(iterator pos)
{
    auto node = pos.node;
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    Node::delete_node(node);
    
    --_size;
    
    return ++pos;
}


/*
 Function: erase range
 Parameters:
  - first: An iterator pointing to the first element to be removed.
  - last: An iterator pointing to the element after the last element
          to be removed.
 Return value: An iterator to the element that replaced first after
               all erases. (Always last)
 
 Description:
    Removes a range of elements [first, last) from the list.
 
 Complexity: O(dist(first, last)) -> Linear in the number of elements
                                     between first and last.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(iterator first, iterator last)
{
    while (first != last)
        erase(first++);
    
    return last;
}


/*
 Function: swap
 Parameters:
  - rhs: The other linked list to swap with
 Return value: None
 
 Description: Swaps the contents of this list with the elements in rhs
              and vice versa.
 
 Complexity: O(1) -> Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::swap(list<T, Alloc>& rhs)
{
    std::swap(_dummy, rhs._dummy);
    std::swap(_size, rhs._size);
}


/*
 Function: clear
 Parameters: None
 Return value: None
 
 Description:
    Removes all elements in the list.
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T, class Alloc>
inline void
list<T, Alloc>::clear() noexcept
{
    erase(begin(), end());
}


/*
 Function: splice
 Parameters:
  - 
 Return value: None
 
 Description:
    
 
 Complexity: Linear in the number of elements being spliced in.
 */
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list& x)
{
    assert(!x.empty());
    splice(pos, x, x.cbegin(), x.cend());
}

template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x)
{
    assert(!x.empty());
    splice(pos, std::move(x), x.cbegin(), x.cend());
}

template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list& x, const_iterator i)
{
    splice(pos, x, i, i.next());
}

template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x, const_iterator i)
{
    splice(pos, std::move(x), i, i.next());
}

template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list& x, const_iterator first, const_iterator last)
{
    assert(first != last);
    
    for (auto it = first; it != last; ++it, ++_size, --x._size);
    
    pos.node->prev->next = first.node;
    last.node->prev->next = pos.node;
    first.node->prev->next = last.node;
    (last--).node->prev = first.node->prev;
    first.node->prev = pos.node->prev;
    pos.node->prev = last.node;
}

template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x, const_iterator first, const_iterator last)
{
    assert(first != last);
    
    for (auto it = first; it != last; ++it, ++_size);
    
    pos.itr->prev->next = first.itr;
    last.itr->prev->next = pos.itr;
    first.itr->prev->next = last.itr;
    (last--).itr->prev = first.itr->prev;
    first.itr->prev = pos.itr->prev;
    pos.itr->prev = last.itr;
}


/*
 Function: remove
 Parameters:
  - element: The value of the element to be removed.
 Return value: None
 
 Description:
    Removes the first occurence of element in the list.
 
 Complexity: O(_size) -> Linear in the index of the element or the size 
                         of the list if the element does not exist.
 */
template <class T, class Alloc>
void
list<T, Alloc>::remove(const_ref element) {
    auto it = std::find(begin(), end(), element);
    
    if (it != end())
        erase(it);
}


/*
 Function: remove if
 Parameters:
  - pred: The predicate used to test all elements in the list.
 Return value: None
 
 Description:
    Removes from the list all elements that satisfy a predicate.
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T, class Alloc>
template <class Predicate>
void
list<T, Alloc>::remove_if(Predicate pred)
{
    for (auto it = begin(); it != end();) {
        if (pred(*it))
            erase(it++);
        else
            ++it;
    }
}


/*
 Function: unique
 Parameters: None
 Return value: None
 
 Description:
    Removes all elements such that it and it's previous
    are equal.
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T, class Alloc>
void
list<T, Alloc>::unique()
{
    unique([](iterator first, iterator second){ return *first == *second; });
}


/*
 Function: unique
 Parameters: 
  - predicate: Determines whether or not an element should be
               removed.
 Return value: None
 
 Description:
 Removes all elements such that it and it's previous
 satisfy a predicate.
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T, class Alloc>
template <class BinaryPredicate>
void
list<T, Alloc>::unique(BinaryPredicate predicate)
{
    auto second = begin();
    auto first = second++;
    
    while (second != end()) {
        if (predicate(first, second))
            erase(second++);
        else
            first = second++;
    }
}


/*
 Function: merge
 Parameters:
  - other: The other list being merged in.
  - compare: Compares elements from the other list with this list.
 Return value: None
 
 Description:
    Combines this sorted list with another sorted list leaving the 
    other list empty after moving all its elements into this list.
 
 Complexity: Linear in the combined size of both lists.
 
 Notes:
  - Functions like insert are not used here since it would
    involve the destruction of an existing node and construction
    of a new one, rather than reconnecting pointers.
 */
template <class T, class Alloc>
void
list<T, Alloc>::merge(list<T, Alloc>& other)
{
    merge(other, [](iterator other_el, iterator this_el) { // TODO: rename these variables
        return *other_el < *this_el;
    });
}

template <class T, class Alloc>
void
list<T, Alloc>::merge(list<T, Alloc>&& other)
{
    merge(std::move(other), [](iterator other_el, iterator this_el) { // TODO: rename these variables
        return *other_el < *this_el;
    });
}

template <class T, class Alloc>
template <class Compare>
void
list<T, Alloc>::merge(list<T, Alloc>& other, Compare compare)
{
    auto itr = begin();
    auto o_itr = other.begin();
    
    // Iterate over this list inserting other elements on successful compare.
    for (; o_itr != other.end() && itr != end();) {
        for (; !compare(o_itr, itr) && itr != end(); ++itr);
        
        if (itr != end()) {
            (o_itr++).node->move_before(itr.node);
            ++_size;
            --other._size;
        }
    }
    
    // If any elements remain in the other list, splice them into the end of this one.
    if (o_itr != other.end())
        splice(cend(), other);
}


template <class T, class Alloc>
template <class Compare>
void
list<T, Alloc>::merge(list<T, Alloc>&& other, Compare compare)
{
    merge(other, compare); // TODO: Find out what should really be done here.
}


/*
 Function: sort
 Parameters:
 - compare: Used to compare elements in the list.
 Return value: None
 
 Description:
    Sorts the elements in the list based on some comparator
    using quicksort.
 
 Complexity: Expected: nlogn, worst case: n^2.
 */
template <class T, class Alloc>
void
list<T, Alloc>::sort()
{
    sort([](iterator it1, iterator it2){ return *it1 < *it2; });
}


template <class T, class Alloc>
template <class Compare>
void
list<T, Alloc>::sort(Compare compare)
{
    std::function<void (iterator, iterator)> do_sort = [&](iterator first, iterator last){
        if (first == last)
            return;
        
        auto pivot = first--;
        
        for (auto itr = pivot; itr != last;) {
            if (compare(itr, pivot))
                (itr++).node->move_before(pivot.node);
            else
                ++itr;
        }
        
        do_sort(++first, pivot);
        do_sort(++pivot, last);
    };
    
    do_sort(begin(), end());
}


/*
 Function: reverse
 Parameters: None
 Return value: None
 
 Description:
    Reverses the list.
 
 Complexity: Linear in the size of the list.
 */
template <class T, class Alloc>
void
list<T, Alloc>::reverse() noexcept
{
    for (auto it = begin(); it != end();)
        (it++).node->move_before(begin().node);
}


#endif /* list_h */
