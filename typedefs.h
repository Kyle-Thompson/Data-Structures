

namespace ads {
    typedef std::size_t size_type;
    template <typename T> using value_type    = T;
    template <typename T> using pointer       = T*;
    //typedef T*          pointer;
    template <typename T> using const_pointer = const T*;
    //typedef const T*    const_ptr;
    template <typename T> using reference     = T&;
    //typedef T&          reference;
    template <typename T> using rvalue_ref    = T&&;
    //typedef T&&         rvalue_ref;
    template <typename T> using const_ref     = const T&;
    //typedef const T&    const_ref;
}
