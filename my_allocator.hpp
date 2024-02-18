#pragma once

#include <memory>

static int a_count = 0;
static int m_count = 0;

template <class T>
class MemoryBlock
{
private:
    std::size_t m_size;
    T* m_head;
    T* m_tail;
    size_t T_sz;
    int m_id;
public:    
    MemoryBlock(int size)
    {
        m_count++;
        m_id = m_count;
        //
        std::cout << "MemoryBlock(" << m_id << ")" << std::endl;
        //
        T_sz = sizeof(T);
        m_size = size * T_sz;
        //
        m_head = new T[size];
        m_tail = m_head;
    }

    T* allocate(std::size_t n)
    {
        auto result = m_tail;
        m_tail += n;
        return result;
    }

    bool canAllocate(std::size_t n)
    {
        return m_size >= (m_tail - m_head) + n * T_sz;
    }

    ~MemoryBlock()
    {
        std::cout << "~MemoryBlock(" << m_id << ")" << std::endl;
        delete[] m_head;
    }
};

template <class T, std::size_t N>
class my_allocator 
{
private:
    std::unique_ptr<MemoryBlock<T>> pool;
    int m_id;
public:    
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    my_allocator()
    {
        a_count++;
        m_id = a_count;
        std::cout << "my_allocator(" << m_id << ")" << std::endl;
        pool = std::make_unique<MemoryBlock<T>>(N);
    }

    ~my_allocator()
    {
        std::cout << "~my_allocator(" << m_id << ")" << std::endl;
    }

    T* allocate (std::size_t n)
    {
        if (!pool->canAllocate(n)) 
            throw std::bad_alloc();

        if (n == 0)
            return nullptr;

        return pool->allocate(n);
    }

    void deallocate (T* p, std::size_t n)
    {
        //  { ToDo }
    }

    template <typename U>
    struct rebind
    {
        using other = my_allocator<U, N>;
    };  

    template <typename U>
    my_allocator(const my_allocator<U, N>&) noexcept {}

};

template <class T, size_t TN, class U, size_t UN>
constexpr bool operator== (const my_allocator<T, TN>& a1, const my_allocator<U, UN>& a2) noexcept
{
    return true;
}

template <class T, size_t TN, class U, size_t UN>
constexpr bool operator!= (const my_allocator<T, TN>& a1, const my_allocator<U, UN>& a2) noexcept
{
    return false;
}