#pragma once

template <class T, std::size_t N>
struct my_allocator {

    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    my_allocator() noexcept {}

    template <class U> 
    my_allocator (const my_allocator <U, N>&) noexcept {}

    T* allocate (std::size_t n)
    {
        if (n > N)
            throw std::bad_alloc();
        
        if (n == 0)
            return nullptr;

        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate (T* p, std::size_t n)
    {
        ::operator delete(p, n * sizeof(T));
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args) 
    {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) 
    {
        p->~T();
    }

    template<class U>
    struct rebind
    {
        typedef my_allocator<U, N> other;
    };

};