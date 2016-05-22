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
  - Get const_reverse_iterator functions working.
  - Test all functions.
  - Test with valgrind for memory leaks. Like for real. Who knows what's happened with these
    allocators now.
  - Update comments of similar functions (all different kinds of merge and such) to only be
    one descriptor comment.
  - Find out what merge(&&, comp) needs different from merge(&, comp). (Also insert& and &&)
  - See how much code can be moved from derived iterators to list_iterator.
  - Find out how the current use of allocators actually works.
  - Make splice(pos, list) constant.
  - Find out what emplace constructed means and how it applies to range constructor.
  - See what iterators can be made into const iterators.
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
    typedef const T*    const_ptr;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;


/* Node definition */
private:
    class Node {
        
    public:
        Node* prev;
        Node* next;
        
        Node();

        Node& detach();
        void move_before(Node*);
        void insert_before(Node*);
        
        static Node* create_dummy();
        static Node* create_node(const_ref, Node*);
        static Node* create_node(rvalue_ref, Node*);
        static void  delete_node(Node*);
    };
    
    class data_node : public Node {
    public:
        using Node::next;
        using Node::prev;
        T data;
        
        data_node(const_ref, Node*);
        data_node(rvalue_ref, Node*);
    };

    
/* Iterators */
private:
    class list_iterator : public std::iterator < std::bidirectional_iterator_tag,
                                                 value_type >

    {
        
    /* Iterator data members */
    protected:
        Node* node;
        
    public:
        list_iterator(Node* n) : node(n) {}
        bool operator==(const list_iterator& rhs) { return node == rhs.node; }
        bool operator!=(const list_iterator& rhs) { return !(*this == rhs); }
    };
    
public:
    class iterator : public list_iterator {
    
        friend class list<T, Alloc>;
        
    private:
        using list_iterator::node;
        
    /* Iterator member functions */
    public:
        iterator(Node* n) : list_iterator(n) {}
        reference operator*()  { return static_cast<data_node*>(node)->data; }
        pointer operator->() { return std::addressof(static_cast<data_node*>(node)->data); }
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
        const_ref operator*()  { return static_cast<data_node*>(node)->data; }
        const_ptr operator->() { return std::addressof(static_cast<data_node*>(node)->data); }
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
    list(iterator, iterator);
    list(const list<T, Alloc>&);
    list(list<T, Alloc>&&);
    list(std::initializer_list<T>);
    ~list();
    
    /* Assignmnent */
    list<T, Alloc>& operator=(const list<T, Alloc>&);
    list<T, Alloc>& operator=(list<T, Alloc>&&);
    list<T, Alloc>& operator=(std::initializer_list<T>);
    
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
    void assign(iterator, iterator);
    void assign(size_type, const_ref);
    void assign(std::initializer_list<value_type>);
    void push_front(const_ref);
    void push_front(rvalue_ref);
    void push_back(const_ref);
    void push_back(rvalue_ref);
    template <class... Args>
    void emplace_front(Args&&...);
    template <class... Args>
        void emplace_back(Args&&...);
    template <class... Args>
        iterator emplace(const_iterator, Args&&...);
    void pop_front();
    void pop_back();
    iterator insert(const_iterator, const_ref);
    iterator insert(const_iterator, size_type, const_ref);
    iterator insert(const_iterator, iterator, iterator);
    iterator insert(const_iterator, rvalue_ref);
    iterator insert(const_iterator, std::initializer_list<value_type>);
    iterator erase(const_iterator);
    iterator erase(const_iterator, const_iterator);
    void swap(list<T, Alloc>&);
    void clear() noexcept;
    
    /* Operations */
    void splice(const_iterator, list<T, Alloc>&);
    void splice(const_iterator, list<T, Alloc>&&);
    void splice(const_iterator, list<T, Alloc>&, const_iterator);
    void splice(const_iterator, list<T, Alloc>&&, const_iterator);
    void splice(const_iterator, list<T, Alloc>&, const_iterator, const_iterator);
    void splice(const_iterator, list<T, Alloc>&&, const_iterator, const_iterator);
    void remove(const_ref);
    template <class Predicate>
        void remove_if(Predicate);
    void unique();
    template <class BinaryPredicate>
        void unique(BinaryPredicate);
    void merge(list<T, Alloc>&);
    void merge(list<T, Alloc>&&);
    template <class Compare>
        void merge(list<T, Alloc>&, Compare);
    template <class Compare>
        void merge(list<T, Alloc>&&, Compare);
    void sort();
    template <class Compare>
        void sort(Compare);
    void reverse() noexcept;
    
};



// Node

/*
 Function: dummy node constructor
 Parameters: None
 
 Description:
    Constructs the node that will act as a sentienl
    in the list.
 
 Complexity: Constant.
 */
template <class T, class Alloc>
list<T, Alloc>::Node::Node()
    : prev(this)
    , next(this)
{}


/*
 Function: data node constructor
 Parameters:
 - element: The data that the node stores.
 - next_node: The node which will be after this node.
 
 Desctiption:
    Constructs a node that holds a piece of data.
 
 Complexity: Constant.
 */

template <class T, class Alloc>
list<T, Alloc>::data_node::data_node(const_ref element, Node* next_node)
    : data(element)
{
    this->insert_before(next_node);
}

template <class T, class Alloc>
list<T, Alloc>::data_node::data_node(rvalue_ref element, Node* next_node)
    : data(std::move(element))
{
    insert_before(next_node);
}


/*
 Function: detach
 Parameters: None
 Return value: A reference to this node.
 
 Description:
    Detaches this node from its surrounding list by
    connecting together its two neighbour nodes and
    setting its next and prev pointers to null.
 
 Complexity: Constant.
 */
template <class T, class Alloc>
typename list<T, Alloc>::Node&
list<T, Alloc>::Node::detach()
{
    next->prev = this->prev;
    prev->next = this->next;
    
    next = prev = nullptr;
    
    return *this;
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
 
 Complexity: Constant.
 */
template <class T, class Alloc>
void
list<T, Alloc>::Node::insert_before(Node* next_node)
{
    next = next_node;
    prev = next_node->prev;
    
    prev->next = this;
    next->prev = this;
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
 
 Description:
    Creates an empty node to act as a sentinel in a list.
 
 Complexity: Constant.
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
 Function: create_node
 Parameters:
  - element: The element which will be stored in the new
             node.
  - next_node: The node in the list that this node will be
               created in front of.
 Return value: A pointer to the new node.
 
 Description:
    Creates a new node to hold 'element'.
 
 Complexity: Constant.
 */
template <class T, class Alloc>
typename list<T, Alloc>::Node*
list<T, Alloc>::Node::create_node(const_ref element, Node* next_node)
{
    typename Alloc::template rebind<data_node>::other alloc;
    auto node = alloc.allocate(1);
    alloc.construct(node, element, next_node);
    
    return node;
}

template <class T, class Alloc>
typename list<T, Alloc>::Node*
list<T, Alloc>::Node::create_node(rvalue_ref element, Node* next_node)
{
    typename Alloc::template rebind<data_node>::other alloc;
    auto node = alloc.allocate(1);
    alloc.construct(node, std::move(element), next_node);
    
    return node;
}


/*
 Function: delete_node
 Parameters:
  - node: The node to be deleted.
 Return value: None
 
 Description:
    Deletes a given node.
 
 Complexity: Constant.
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
 Function: constructor
 Parameters:
  - n: The number of times to insert 'element'.
  - element: The element to be inserted.
  - first: Iterator to the first element to be inserted.
  - last: Iterator to one past the last element to be inserted.
  - rhs: The list which is being either copied or moved from.
  - il: Initializer list of elements.
 Return value: None
 
 Description:
  1.
  2.
  3.
  4. 
  5.
  6.
 
 Complexity:
  1. Constant.
  2. Linear in n.
  3. Linear in distance between first and last.
  4. Linear in size of rhs.
  5. Constant.
  6. Linear in the size of il.
 */

// 1. default constructor
template <class T, class Alloc>
list<T, Alloc>::list()
    : _dummy(Node::create_dummy())
{}

// 2. fill constructor
template <class T, class Alloc>
list<T, Alloc>::list(size_type n, const_ref element)
    : _dummy(Node::create_dummy())
{
    insert(end(), n, element);
}

// 3. range constructor
template <class T, class Alloc>
list<T, Alloc>::list(iterator first, iterator last)
    : _dummy(Node::create_dummy())
{
    insert(end(), first, last);
}

// 4. copy constructor
template <class T, class Alloc>
list<T, Alloc>::list(const list<T, Alloc>& rhs)
    : _dummy(Node::create_dummy())
{
    insert(end(), rhs.begin(), rhs.end());
}

// 5. move constructor
template <class T, class Alloc>
list<T, Alloc>::list(list<T, Alloc>&& rhs)
    : _dummy(Node::create_dummy())
{
    splice(end(), std::move(rhs));
}

// 6. initializer list constructor
template <class T, class Alloc>
list<T, Alloc>::list(std::initializer_list<T> il)
    : _dummy(Node::create_dummy())
{
    insert(cend(), il);
}


/*
 Function: destructor
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



// Assignment

/*
 Function: operator=
 Parameters:
  - rhs: The other list which is being assigned from.
  - il: An initializer list of new elements for the list.
 Return value: A reference to this list.
 
 Description:
    Replaces contents of this list with...
    1. elements from rhs without affecting rhs.
    2.
    3. initializer list assignment:
 
 Complexity: Linear in the size of this list and (for 1 and
             3) the size of rhs or il.
 
 */

// 1. copy assignment
template <class T, class Alloc>
list<T, Alloc>&
list<T, Alloc>::operator=(const list<T, Alloc>& rhs)
{
    clear();
    insert(cbegin(), rhs.begin(), rhs.end());
    
    return *this;
}

// 2. move assignment
template <class T, class Alloc>
list<T, Alloc>&
list<T, Alloc>::operator=(list<T, Alloc>&& rhs)
{
    clear();
    splice(begin(), rhs);
    
    return *this;
}

// 3. initializer list assignment
template <class T, class Alloc>
list<T, Alloc>&
list<T, Alloc>::operator=(std::initializer_list<T> il)
{
    assign(il);
    
    return *this;
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
    return reverse_iterator(end());
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
    return reverse_iterator(begin());
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
    return const_reverse_iterator(end());
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
    return const_reverse_iterator(begin());
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
    return static_cast<data_node*>(_dummy->next)->data;
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
    return static_cast<data_node*>(_dummy->prev)->data;
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

/*
 Function: assign
 Parameters:
  - first: The first element in a range.
  - last: One past the last element in a range.
  - n: The number of times to add 'element'.
  - element: The element to be repeatedly added.
  - il: An initializer list of new elements.
 Return value: None
 
 Description:
    Replaces the contents of the current list with...
    1. a range of elements in a collection.
    2. one element repeated n times.
    3. an initializer list of new elements.
 
 Complexity: Linear in the current size of the list
             and the number of elements replacing them.
 */

// 1. assign range
template <class T, class Alloc>
void
list<T, Alloc>::assign(iterator first, iterator last)
{
    clear();
    insert(begin(), first, last);
}

// 2. assign fill
template <class T, class Alloc>
void
list<T, Alloc>::assign(size_type n, const_ref element)
{
    clear();
    insert(begin(), n, element);
}

// 3. assign initializer list
template <class T, class Alloc>
void
list<T, Alloc>::assign(std::initializer_list<T> il)
{
    clear();
    insert(begin(), il);
}


/*
 Function: push_front
 Parameters:
  - element: The element being added to the front of the list.
 Return value: None
 
 Description:
    Adds a given element into the front of the list.
 
 Complexity: Constant
 */

template <class T, class Alloc>
void
list<T, Alloc>::push_front(const T& element)
{
    insert(begin(), element);
}

template <class T, class Alloc>
void
list<T, Alloc>::push_front(T&& element)
{
    insert(cbegin(), std::move(element));
}


/*
 Function: push_back
 Parameters:
  - element: The element being added to the list.
 Return value: None
 
 Description:
    Adds a given element into the back of the list.
 
 Complexity: Constant
 */

template <class T, class Alloc>
void
list<T, Alloc>::push_back(const T& element)
{
    insert(end(), element);
}

template <class T, class Alloc>
void
list<T, Alloc>::push_back(T&& element)
{
    insert(cend(), std::move(element));
}


/*
 Function: emplace
 Parameters:
  - args: Arguments used to construct the new T object.
  - pos: The iterator to insert the new element before.
 Return value: None (front and back) or an iterator to the
               new element.
 
 Description:
    Creates a new T object and adds it to the front, back or
    a given position in the list.
 
 Complexity: Complexity of T(args) constructor.
 */

template <class T, class Alloc>
template <class... Args>
void
list<T, Alloc>::emplace_front(Args&&... args)
{
    emplace(begin().node, std::forward<Args>(args)...);
}

template <class T, class Alloc>
template <class... Args>
void
list<T, Alloc>::emplace_back(Args&&... args)
{
    emplace(end().node, std::forward<Args>(args)...);
}

template <class T, class Alloc>
template <class... Args>
typename list<T, Alloc>::iterator
list<T, Alloc>::emplace(const_iterator pos, Args&&... args)
{
    Node* n = Node::create_node(T(std::forward<Args>(args)...), pos().node);
    
    return iterator(n);
}


/*
 Function: pop_front
 Parameters: None
 Return value: None
 
 Description:
    Removes the first element in the list from the list and returns it.
 
 Complexity: Constant.
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
 
 Complexity: Constant.
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
  - n: The number of duplicate elements to be inserted.
  - element: The new item to be inserted.
  - first: The first element in the range of elements to be copied.
  - last: One element past the last to be inserted.
  - il: An initializer list of new values to be added to the list.
 Return value: An iterator pointing to the newly inserted element.
 
 Description:
  1. Adds an element into the list before pos.
  2. Adds an element n times into the list at a given position.
  3. Adds elements [first, last) into the list given by an
     iterator range.
  4. Adds an element into the list before pos.
  5. Adds all the items in an initializer list to the list at a given
     position.
 
 Complexity: Linear in the number of elements being inserted.
 */

// 1. single element
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, const_ref element)
{
    auto node = Node::create_node(element, pos.node);
    
    node->prev->next = node;
    node->next->prev = node;
    
    ++_size;
    
    return iterator(node);
}

// 2. fill
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, size_type n, const_ref element)
{
    while (--n > 0)
        insert(pos, element);
    
    return insert(pos, element);
}

// 3. range
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, iterator first, iterator last)
{
    while (first != last)
        insert(pos, *first++);
    
    return iterator(pos.node);
}

// 4. move
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, rvalue_ref element)
{
    return insert(pos, element);
}

// 5. initializer list
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::insert(const_iterator pos, std::initializer_list<T> il)
{
    for (auto it : il)
        insert(pos, it);
    
    return iterator(pos.node->prev);
}


/*
 Function: erase
 Parameters:
  - pos: An iterator to the element to be removed.
  - first: An iterator to the first element to be removed.
  - last: An iterator to one past the last element to be removed.
 Return value: An iterator to the element that replaces the first
               element which was removed.
 
 Description:
    Removes...
    1. an element from the list.
    2. a range of elements from the list. [first, last)
 
 Complexity: Linear in the number of elements being removed.
 */
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(const_iterator pos)
{
    auto node = pos.node;
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    Node::delete_node(node);
    
    --_size;
    
    return iterator(pos.node->next);
}

template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(const_iterator first, const_iterator last)
{
    while (first != last)
        erase(first++);
    
    return iterator(last.node);
}


/*
 Function: swap
 Parameters:
  - rhs: The other linked list to swap with
 Return value: None
 
 Description: Swaps the contents of this list with the elements in rhs
              and vice versa.
 
 Complexity: Constant.
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
 
 Complexity: Linear in the size of the list.
 */
template <class T, class Alloc>
inline void
list<T, Alloc>::clear() noexcept
{
    erase(cbegin(), cend());
}


/*
 Function: splice
 Parameters:
  - pos: The position which all the new elements should be added
         behind.
  - x: The list from which the new elements are being spliced in.
  - i: The index of the element in x to be spliced in.
  - first: An iterator to the first element to be moved to this list.
  - last: An iterator to one past the last element to be moved to
          this list.
 Return value: None
 
 Description:
  1. Moves the entirety of another list into this list behind pos.
  2. Moves a particular element from x into this list behind pos.
  3. Moves a range of elements from x into this list behind pos.
 
 Complexity: Linear in the number of elements being spliced in.
 */

// 1. entire list
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list& x)
{
    assert(!x.empty());
    splice(pos, x, x.cbegin(), x.cend());
}

// 1. entire list
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x)
{
    assert(!x.empty());
    splice(pos, std::move(x), x.cbegin(), x.cend());
}

// 2. single element
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list& x, const_iterator i)
{
    splice(pos, x, i, i.next());
}

// 2. single element
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x, const_iterator i)
{
    splice(pos, std::move(x), i, i.next());
}

// 3. element range
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

// 3. element range
template <class T, class Alloc>
void
list<T, Alloc>::splice(const_iterator pos, list&& x, const_iterator first, const_iterator last)
{
    assert(first != last);
    
    for (auto it = first; it != last; ++it, ++_size, --x._size);
    
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
 
 Complexity: Linear in the index of the element or the size of the 
             list if the element does not exist.
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
 
 Complexity: Linear in the size of the list.
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
 
 Complexity: Linear in the size of the list.
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
 
 Complexity: Linear in the size of the list.
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
    auto o_itr = other.begin();
    
    // Iterate over this list inserting other elements on successful compare.
    for (auto itr = begin(); itr != end() && o_itr != other.end();) {
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
    using quicksort. (TODO: find out if stable)
 
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
        
        for (auto itr = pivot; itr != last;)
            if (compare(itr++, pivot))
                itr.node->prev->move_before(pivot.node);
        
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