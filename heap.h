/*
 *
 */

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
