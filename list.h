/*
 File:   list.h
 Author: Kyle Thompson
 
 Purpose:
    This class is meant to be a fully standard compliant linked list which will act as a
    foundation for more linked list based data structures.
 
 Implementation:
  - A custom random access iterator is implemented for accessing and iterating through the
    elements. 
  - A single dummy node is used to simplify insertion and deletion operations as well as 
    iterator functions like end() and rbegin().
 
 TODO:
  - Find out how to correctly use an allocator and use it.
  - Test all functions.
  - Find out if there's a viable way to make insert and erase take a const iterator.
  - Make sure that elements being inserted by range aren't still references to one another.
  - Test with valgrind for memory leaks
  - Find a good category for operator=.
  - Find out if ListIterator inheriting from std::iterator is even necessary.
  - Find out if _dummy can be a unique_ptr
  - Removed templating from iterator.
  - Find out how to properly do insert given an rvalue reference.
  - Have push_front and push_back use insert.
  - Find how to correctly implement const_iterator.
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
        
        // Constructor for dummy node.
        Node()
            : prev(this)
            , next(this)
        {}
        
        // Constructor for data node.
        Node(const_ref element, Node* prevptr, Node* nextptr)
            : prev(prevptr)
            , next(nextptr)
            , data(element)
        {}
    };

    
/* Iterators */
public:
    class iterator : public std::iterator< std::bidirectional_iterator_tag,  // category
                                           T,                                // type
                                           std::ptrdiff_t,                   // distance
                                           T*,                               // pointer
                                           T& >                              // reference
    {
    
        friend class list<T, Alloc>;
        
    /* Iterator data members */
    private:
        Node* itr;
        
    /* Iterator member functions */
    public:
        iterator(Node* n) : itr(n) {}
        reference operator*()  { return itr->data; }
        reference operator->() { return itr->data; }
        iterator& operator++() { itr = itr->next; return *this; }
        iterator operator++(int) { iterator temp(*this); itr = itr->next; return temp; }
        iterator& operator--() { itr = itr->prev; return *this; }
        iterator operator--(int) { iterator temp(*this); itr = itr->prev; return temp; }
        bool operator==(const iterator& rhs) { return itr->data == rhs.itr->data; }
        bool operator!=(const iterator& rhs) { return !(itr == rhs.itr); }
    };
    
    class const_iterator : public std::iterator< std::bidirectional_iterator_tag,  // category
                                                 T,                                // type
                                                 std::ptrdiff_t,                   // distance
                                                 T*,                               // pointer
                                                 T& >                              // reference
    {
        
        friend class list<T, Alloc>;
        
    /* Iterator data members */
    private:
        Node* itr;
        
    /* Iterator member functions */
    public:
        const_iterator(Node* n) : itr(n) {}
        const_ref operator*()  { return itr->data; }
        const_ref operator->() { return itr->data; }
        const_iterator& operator++() { itr = itr->next; return *this; }
        const_iterator operator++(int) { const_iterator temp(*this); itr = itr->next; return temp; }
        const_iterator& operator--() { itr = itr->prev; return *this; }
        const_iterator operator--(int) { const_iterator temp(*this); itr = itr->prev; return temp; }
        bool operator==(const iterator& rhs) { return itr->data == rhs.itr->data; }
        bool operator!=(const iterator& rhs) { return !(itr == rhs.itr); }
    };
    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    

/* Data members */
private:
    Node* _dummy;          // Dummy node between start and end of list.
    size_type _size = 0;   // Number of real elements in list.
    

/* Internal functions */
private:
    Node* _alloc_dummy();                                                     // Not yet implemented.
    
    
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
    : _dummy(new Node())
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
    : _dummy(new Node())
{
    insert(end(), n, element);
}


/*
 Function: range constructor.
 */
template <class T, class Alloc>
list<T, Alloc>::list(iterator, iterator)
    : _dummy(new Node())
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
    : _dummy(new Node())
{
    insert(end(), rhs.begin(), rhs.end());
}


/*
 Function: move constructor.
 */
template <class T, class Alloc>
list<T, Alloc>::list(list<T, Alloc>&&)
    : _dummy(new Node())
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
    : _dummy(new Node())
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
    delete _dummy;
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
    assert(!empty());
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
    assert(!empty());
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
    assert(!empty());
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
    auto node = new Node(element, _dummy, _dummy->next);
    
    _dummy->next->prev = node;
    _dummy->next = node;
    
    ++_size;
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
    auto node = new Node(std::move(element), _dummy, _dummy->next);

    _dummy->next->prev = node;
    _dummy->next = node;
    
    ++_size;
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

    auto node = new Node(element, _dummy->prev, _dummy);

    _dummy->prev->next = node;
    _dummy->prev = node;
    
    ++_size;
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
    auto node = new Node(std::move(element), _dummy->prev, _dummy);
    
    _dummy->prev->next = node;
    _dummy->prev = node;
    
    ++_size;
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
list<T, Alloc>::insert(iterator pos, const T& element)
{
    auto node = new Node(element, pos.itr->prev, pos.itr);
    
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
    auto node = pos.itr;
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    --_size;
    
    delete node;
    
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


//void splice(const_iterator, list<T, Alloc>&);                                       // Not yet implemented.
//void splice(const_iterator, list<T, Alloc>&&);                                      // Not yet implemented.
//void splice(const_iterator, list<T, Alloc>&, const_iterator);                       // Not yet implemented.
//void splice(const_iterator, list<T, Alloc>&&, const_iterator);                      // Not yet implemented.
//void splice(const_iterator, list<T, Alloc>&, const_iterator, const_iterator);       // Not yet implemented.
//void splice(const_iterator, list<T, Alloc>&&, const_iterator, const_iterator);      // Not yet implemented.


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
 Parameters: predicate
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


//void merge(list<T, Alloc>&);                                                        // Not yet implemented.
//void merge(list<T, Alloc>&&);                                                       // Not yet implemented.
//template <class Compare>
//void merge(list<T, Alloc>&, Compare);                                           // Not yet implemented.
//template <class Compare>
//void merge(list<T, Alloc>&&, Compare);                                          // Not yet implemented.


/*
 Function: sort
 Parameters: None
 Return value: None
 
 Description:
 Sorts the elements in the list.
 
 Complexity: O(nlogn) -> Where n is _size.
 */
template <class T, class Alloc>
void
list<T, Alloc>::sort()
{
    sort([](iterator it1, iterator it2){ return *it1 < *it2; });
}


/*
 Function: sort
 Parameters: None
 Return value: None
 
 Description: 
    Sorts the elements in the list based on some comparator 
    using quicksort.
 
 Complexity: O(nlogn) -> Where n is _size.
 */
template <class T, class Alloc>
template <class Compare>
void
list<T, Alloc>::sort(Compare compare)
{
    std::function<void (iterator, iterator)> do_sort = [&](iterator first, iterator last){
        if (first == last)
            return;
        
        auto pivot = first--;

        auto move_left_of_pivot = [&](iterator it){
            auto& node = it.itr;
            auto& piv_node = pivot.itr;
            
            node->next->prev = node->prev;
            node->prev->next = node->next;
            
            node->prev = piv_node->prev;
            node->next = piv_node;
            
            piv_node->prev->next = node;
            piv_node->prev = node;
        };
        
        
        for (auto itr = pivot; itr != last;) {
            if (compare(itr, pivot))
                move_left_of_pivot(itr++);
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
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T, class Alloc>
void
list<T, Alloc>::reverse() noexcept
{
    auto move_front = [&](iterator it){
        auto& node = it.itr;
        
        node->next->prev = node->prev;
        node->prev->next = node->next;
        
        node->next = _dummy->next;
        node->prev = _dummy;
        
        _dummy->next = node;
        node->next->prev = node;
    };
    
    for (auto it = begin(); it != end();)
        move_front(it++);
}


#endif /* list_h */