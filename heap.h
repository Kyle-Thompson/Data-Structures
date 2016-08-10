/*
 *
 */

#include <algorithm>  // std::swap
#include <vector> // replace this with custom vector when ready.


template <class T>
class heap {

/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_ptr;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;


/* Data members */
private:
    std::vector data;


/* Member functions */
public:
    /* Constructors */
    heap();
    ~heap();

    /* Assignment */

    /* Capacity */
    bool empty() const;
    size_type size() const;

    /* Element access */
    reference get() const;

    /* Modifiers */
    void push(const_ref);
    void push(rvalue_ref);
    template <class... Args>
        emplace(Args&&...);
    void pop();
    // add something for group insert.
    void swap(heap<T>&);
    void clear() noexcept;

    /* Operations */
    void merge(heap<T>&);
    void merge(heap<T>&&);
    template <class Compare>
        void merge(heap<T>&, Compare);
    template <class Compare>
        void merge(heap<T>&&, Compare);


/* Helpers */
private:
    auto parent = [](size_type c) { return (curr - (curr+1)%2)/2; }
};



// Constructors

/*
 Function: constructor
 Parameters: None
 Return value: None

 Description:
    Makes an empty heap.

 Complexity:
    Constant.
 */

// 1. default
template <class T>
heap<T>::heap()
{}


/*
 Function: destructor
 Parameters: None
 Return value: None

 Description:
    Clears all data within the heap.
 */
template <class T>
heap<T>::~heap()
{} // Since destroying this will likely cause vector to clean up, maybe nothing is needed.



// Assignment

/*
 
 */



// Capacity

/*
 Function: empty
 Parameters: None
 Return value: Whether or not the heap is empty.
 */
template <class T>
inline bool
heap<T>::empty()
{
    return data.empty();
}


/*
 Function: size
 Parameters: None
 Return value: The size of the heap.
 */
template <class T>
inline bool
heap<T>::empty()
{
    return data.size();
}



// Element access

/*
 Function: get
 Parameters: None
 Return value: A reference to the head element of the heap.
 */
template <class T>
inline T&
heap<T>::get()
{
    assert(!empty());
    return data[0];
}



// Modifiers

/*
 Function: push
 Parameters: 
 */
template <class T>
void
heap<T>::push(const_ref element)
{
    size_type curr = data.size();
    data.push_back(element);

    for (size_type p = parent(curr); data[p] < data[curr]; curr = p, p = parent(curr))
        std::swap(data[parent], data[curr]);
}

template <class T>
void
heap<T>::push(rvalue_ref element)
{
    
}


/*
 Function: emplace
 */
template <class T, class... Args>
void
heap<T>::emplace(Args&&...)
{
    
}


/*
Function: pop
Parameters: None
Return value: None

Description:

Complexity:
 */
template <class T>
void
heap<T>::pop()
{
    
}
    

void swap(heap<T>&);
void clear() noexcept;

/* Operations */
void merge(heap<T>&);
void merge(heap<T>&&);
template <class Compare>
    void merge(heap<T>&, Compare);
template <class Compare>
    void merge(heap<T>&&, Compare);

