/*
 File:   LinkedList.h
 Author: Kyle Thompson
 
 Purpose:
    This class is meant to be a fully standard compliant linked list which will act as a
    foundation for more linked list based data structures.
 
 Implementation:
  - A custom random access iterator is implemented for accessing and iterating through the
    elements. 
  - Two dummy nodes are used to cleanly allow iterator functions like end() and rbegin().
 
 TODO:
  - Find out how to correctly use an allocator and use it.
  - Test all functions.
  - Find out if there's a viable way to make insert and erase take a const iterator.
  - Make sure that elements being inserted by range aren't still references to one another.
  - Test insert functions.
  - Initializer list constructor
  - Test with valgrind for memory leaks
  - Find a good category for operator=.
  - Find out if nodes are being correctly removed since they're shared pointers.
 */


#ifndef LinkedList_h
#define LinkedList_h

#include <algorithm>   // move
#include <cassert>     // assert
#include <cstddef>     // ptrdiff_t
#include <iterator>    // iterator
#include <memory>      // allocator
#include <utility>     // swap

template <class T>
class LinkedList {
    
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
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;
        T data;
        
        // Constructor for dummy node.
        Node()
            : prev(nullptr)
            , next(nullptr)
        {}
        
        // Constructor for data node.
        Node(const_ref element)
            : prev(nullptr)
            , next(nullptr)
            , data(element)
        {}
    };

    
/* Iterator */
public:
    template <class N>
    class ListIterator : public std::iterator< std::random_access_iterator_tag,  // category
                                               T,                                // type
                                               std::ptrdiff_t,                   // distance
                                               T*,                               // pointer
                                               T& >                              // reference
    {
    
        friend class LinkedList<T>;
        
    /* Iterator data members */
    private:
        std::shared_ptr<N> itr;
        
    /* Iterator member functions */
    public:
        ListIterator(std::shared_ptr<N> n) : itr(n) {}
        reference operator*()  { return itr->data; }
        reference operator->() { return itr->data; }
        ListIterator& operator++() { itr = itr->next; return *this; }
        ListIterator operator++(int) { ListIterator temp(*this); itr = itr->next; return temp; }
        bool operator==(const ListIterator& rhs) { return itr->data == rhs.itr->data; }
        bool operator!=(const ListIterator& rhs) { return !(itr == rhs.itr); }
    };

    typedef ListIterator<Node> iterator;
    typedef ListIterator<const Node> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    

/* Data members */
private:
    std::shared_ptr<Node> _begin;  // Dummy node at start of list.
    std::shared_ptr<Node> _end;    // Dummy node at end of list.
    std::shared_ptr<Node> _head;   // First real element.
    std::shared_ptr<Node> _tail;   // Last real element.
    size_type _size;               // Number of real elements in list.
    
    
/* Member functions */
public:
    /* Constructors */
    LinkedList();
    LinkedList(size_type, const_ref);                                                  // Not yet implemented.
    LinkedList(iterator, iterator);                                                    // Not yet implemented.
    LinkedList(const LinkedList<T>&);
    LinkedList(LinkedList<T>&&);                                                       // Not yet implemented.
    LinkedList(std::initializer_list<T>);                                              // Not yet implemented.
    ~LinkedList();
    
    // where to even put this assignment operator?
    LinkedList<T>& operator=(LinkedList<T>);                                           // Not yet implemented.
    
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
    void assign(std::initializer_list<T>);                                             // Not yet implemented.
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
    reference pop_front();
    reference pop_back();
    iterator insert(iterator, const_ref);
    iterator insert(iterator, size_type, const_ref);
    iterator insert(iterator, const_iterator, const_iterator);
    iterator insert(iterator, rvalue_ref);
    iterator insert(iterator, std::initializer_list<value_type>);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void swap(LinkedList<T>&);
    void clear() noexcept;
    
    /* Operations */
    void splice(const_iterator, LinkedList<T>&);                                       // Not yet implemented.
    void splice(const_iterator, LinkedList<T>&&);                                      // Not yet implemented.
    void splice(const_iterator, LinkedList<T>&, const_iterator);                       // Not yet implemented.
    void splice(const_iterator, LinkedList<T>&&, const_iterator);                      // Not yet implemented.
    void splice(const_iterator, LinkedList<T>&, const_iterator, const_iterator);       // Not yet implemented.
    void splice(const_iterator, LinkedList<T>&&, const_iterator, const_iterator);      // Not yet implemented.
    void remove(const_ref);                                                            // Not yet implemented.
    template <class Predicate>
        void remove_if(Predicate);                                                     // Not yet implemented.
    void unique();                                                                     // Not yet implemented.
    template <class BinaryPredicate>
        void unique(BinaryPredicate);                                                  // Not yet implemented.
    void merge(LinkedList<T>&);                                                        // Not yet implemented.
    void merge(LinkedList<T>&&);                                                       // Not yet implemented.
    template <class Compare>
        void merge(LinkedList<T>&, Compare);                                           // Not yet implemented.
    template <class Compare>
        void merge(LinkedList<T>&&, Compare);                                          // Not yet implemented.
    void sort();                                                                       // Not yet implemented.
    template <class Compare>
        void sort(Compare);                                                            // Not yet implemented.
    void reverse() noexcept;                                                           // Not yet implemented.
    
};



// Constructors

/*
 Function: default constructor
 Parameters: None
 Return value: None
 
 Description:
    Initializes a default, empty linked list.
 */
template <class T>
LinkedList<T>::LinkedList()
    : _begin(std::make_shared<Node>())
    , _end  (std::make_shared<Node>())
    , _head (nullptr)
    , _tail (nullptr)
    , _size (0)
{}


/*
 Function: fill constructor
 */
template <class T>
LinkedList<T>::LinkedList(size_type, const_ref)
{
    
}


/*
 Function: range constructor.
 */
template <class T>
LinkedList<T>::LinkedList(iterator, iterator)
{
    
}


/*
 Function: copy constructor
 Parameters: 
  - rhs: Reference to other list being copied from.
 Return value: None
 
 Description:
    Initializes a linked list as a deep copy of another
    linked list.
 */
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
    : _begin(std::make_shared<Node>())
    , _end  (std::make_shared<Node>())
    , _head (nullptr)
    , _tail (nullptr)
    , _size (0)
{
    for (auto data : rhs)
        push_back(data);
}


/*
 Function: move constructor.
 */
template <class T>
LinkedList<T>::LinkedList(LinkedList<T>&&)
{
    
}


/*
 Function: initializer list constructor
 */
template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T>)
{
    
}



/*
 Function: Destructor
 Parameters: None
 Return value: None
 
 Description:
    Clears all nodes and associated data within the linked list.
 */
template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
}



// Iterator

/*
 Function: begin
 Parameters: None
 Return value: An iterator to the first position in the list.
 */
template <class T>
inline typename LinkedList<T>::iterator
LinkedList<T>::begin() const
{
    assert(!empty());
    return _head;
}


/*
 Function: end
 Parameters: None
 Return value: An iterator to the past-the-end position in the list.
 */
template <class T>
inline typename LinkedList<T>::iterator
LinkedList<T>::end() const
{
    assert(!empty());
    return _end;
}


/*
 Function: cbegin
 Parameters: None
 Return value: A const iterator to the first position in the list.
 */
template <class T>
inline typename LinkedList<T>::const_iterator
LinkedList<T>::cbegin() const
{
    assert(!empty());
    return const_iterator(_head);
}


/*
 Function: cend
 Parameters: None
 Return value: A const iterator to the past-the-end position in the list.
 */
template <class T>
inline typename LinkedList<T>::const_iterator
LinkedList<T>::cend() const
{
    assert(!empty());
    return const_iterator(_end);
}


/*
 Function: rbegin
 Parameters: None
 Return value: A reverse iterator to the first position in the reversed
               list. (Last element in the real list.)
 */
template <class T>
inline typename LinkedList<T>::reverse_iterator
LinkedList<T>::rbegin() const
{
    assert(!empty());
    return _tail;
}


/*
 Function: rend
 Parameters: None
 Return value: A reverse iterator to the past-the end position in the 
               reversed list. (One before first position in real list.)
 */
template <class T>
inline typename LinkedList<T>::reverse_iterator
LinkedList<T>::rend() const
{
    assert(!empty());
    return _begin;
}


/*
 Function: crbegin
 Parameters: None
 Return value: An const reverse iterator to the first position in the 
               reversed list. (Last element in the real list.)
 */
template <class T>
inline typename LinkedList<T>::const_reverse_iterator
LinkedList<T>::crbegin() const
{
    assert(!empty());
    return _tail;
}


/*
 Function: crend
 Parameters: None
 Return value: A const reverse iterator to the past-the-end position in 
               the reversed list. (One before first position in real list.)
 */
template <class T>
inline typename LinkedList<T>::const_reverse_iterator
LinkedList<T>::crend() const
{
    assert(!empty());
    return _begin;
}



// Capacity

/*
 Function: empty
 Parameters: None
 Return value: Whether or not the list is empty.
 */
template <class T>
inline bool
LinkedList<T>::empty() const
{
    return _size == 0;
}


/*
 Function: size
 Parameters: None
 Return value: The size of the list.
 */
template <class T>
inline std::size_t
LinkedList<T>::size() const
{
    return _size;
}


// Element access

/*
 Function: front
 Parameters: None
 Return value: A reference to the first element in the list.
 */
template <class T>
inline T&
LinkedList<T>::front() const
{
    assert(!empty());
    return _head->data;
}


/*
 Function: last
 Parameters: None
 Return value: A reference to the last element in the list.
 */
template <class T>
inline T&
LinkedList<T>::last() const
{
    assert(!empty());
    return _tail->data;
}


/*
 Function: at
 Parameters:
  - index: The position within the list to access.
 Return value: A reference to the index-th position in the list.
 */
template <class T>
T&
LinkedList<T>::at(size_type index) const
{
    assert (index < _size);
    
    auto node = _head;
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
template <class T>
inline T&
LinkedList<T>::operator[](size_type index) const
{
    return at(index);
}


// Modifiers


//void assign(iterator, iterator);                                                   // Not yet implemented.
//void assign(size_type, const_ref);                                                 // Not yet implemented.
//void assign(std::initializer_list<T>);                                             // Not yet implemented.



/*
 Function: push_front
 Parameters:
  - element: A const reference to the element being added to the list.
 Return value: None
 
 Description:
    Adds a given element into the front of the list.
 
 Complexity: O(1) -> Constant.
 */
template <class T>
void
LinkedList<T>::push_front(const T& element)
{
    std::shared_ptr<Node> node = std::make_shared<Node> (element);
    
    if (empty()) {
        _head = node;
        _tail = node;
        node->next = _end;
        _end->prev = node;
    } else {
        _head->prev = node;
        node->next = _head;
        _head = node;
    }
    
    node->prev = _begin;
    _begin->next = node;
    
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
template <class T>
void
LinkedList<T>::push_front(T&& element)
{
    std::shared_ptr<Node> node = std::make_shared<Node> (std::move(element));
    
    if (empty()) {
        _head = node;
        _tail = node;
        node->next = _end;
        _end->prev = node;
    } else {
        _head->prev = node;
        node->next = _head;
        _head = node;
    }
    
    node->prev = _begin;
    _begin->next = node;
    
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
template <class T>
void
LinkedList<T>::push_back(const T& element)
{

    std::shared_ptr<Node> node = std::make_shared<Node>(element);
    
    if (empty()) {
        _head = node;
        _tail = node;
        node->prev = _begin;
        _begin->next = node;
    } else {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    
    node->next = _end;
    _end->prev = node;
    
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
template <class T>
void
LinkedList<T>::push_back(T&& element)
{
    std::shared_ptr<Node> node = std::make_shared<Node>(std::move(element));
    
    if (empty()) {
        _head = node;
        _tail = node;
        node->prev = _begin;
        _begin->next = node;
    } else {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    
    node->next = _end;
    _end->prev = node;
    
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
template <class T>
template <class... Args>
void
LinkedList<T>::emplace_front(Args&&... args)
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
template <class T>
template <class... Args>
void
LinkedList<T>::emplace_back(Args&&... args)
{
    // TODO: Fill in function definition.
}


/*
 Function: pop_front
 Parameters: None
 Return value: The element formerly in the first position in the list.
 
 Description:
    Removes the first element in the list from the list and returns it.
 
 Complexity: O(1) -> Constant.
 */
template <class T>
T&
LinkedList<T>::pop_front()
{
    assert(!empty());
    
    T& element = _head->data;
    --_size;
    
    if (empty()) {
        _head = nullptr;
        _tail = nullptr;
        _begin->next = nullptr;
        _end->prev = nullptr;
    } else {
        // auto old = _head; // should this be getting explicityly freed or something?
        _head = _head->next;
        _head->prev = _begin;
        _begin->next = _head;
    }
    
    return element;
}


/*
 Function: pop_back
 Parameters: None
 Return value: The element formerly in the last position in the list.
 
 Description:
    Removes the first element in the list from the list and returns it.
 
 Complexity: O(1) -> Constant.
 */
template <class T>
T&
LinkedList<T>::pop_back()
{
    assert(!empty());
    
    T& element = _tail->data;
    --_size;
    
    if (empty()) {
        _head = nullptr;
        _tail = nullptr;
        _begin->next = nullptr;
        _end->prev = nullptr;
    } else {
        _tail = _tail->prev;
        _tail->next = _end;
        _end->prev = _tail;
    }
    
    return element;
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::insert(iterator pos, const T& element)
{
    std::shared_ptr<Node> node = std::make_shared<Node>(element);
    
    // Assign node's next and prev.
    node->prev = pos.itr->prev;
    node->next = pos.itr;
    
    // Reassign node's neighbours to point to node.
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::insert(iterator pos, size_type n, const_ref element)
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::insert(iterator pos, const_iterator first, const_iterator last)
{
    while (--last != first)
        insert(pos, *last);
    
    return insert(pos, *first);
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::insert(iterator pos, rvalue_ref element)
{
    return insert(pos, std::move(element));
}


/*
 Function: insert
 Parameters:
  - pos: An iterator at the position which the new element will be
         inserted in front of.
  - init_list: An initializer list of new values to be added to the list.
 
 Description:
    Adds all the items in an initializer list to the list at a given 
    position.
 
 Complexity: O(|init_list|) -> Linear in the size of the initializer list.
 */
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::insert(iterator pos, std::initializer_list<T> init_list)
{
    for (auto& it = init_list.rbegin; it != init_list.rend(); --it) // TODO: should this be ++it since it's a reverse iterator?
        insert(pos, *it);
    
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::erase(iterator pos)
{
    auto& node = pos.itr;
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    --_size;
    
    return ++pos;
}


/*
 Function: erase
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
template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::erase(iterator first, iterator last)
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
template <class T>
void
LinkedList<T>::swap(LinkedList<T>& rhs)
{
    std::swap(*this, rhs);
}


/*
 Function: clear
 Parameters: None
 Return value: None
 
 Description:
    Removes all elements in the list.
 
 Complexity: O(_size) -> Linear in the size of the list.
 */
template <class T>
inline void
LinkedList<T>::clear() noexcept
{
    erase(begin(), end());
}


#endif /* LinkedList_h */