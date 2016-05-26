#ifndef vector_h
#define vector_h

template <class T, class Alloc = std::allocator<T>>
class vector {
    
/* Type definitions */
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_ptr;
    typedef T&          reference;
    typedef T&&         rvalue_ref;
    typedef const T&    const_ref;
    
/* Iterators */
    
    
/* Data members */
    T* _data;
    size_type _size = 0;
    
    
/* Member functions */
    
    
};

#endif /* vector_h */
