#include <iostream>
#include <memory>

template <class T, class Alloc = std::allocator<T>>
class my_container {
public:
    my_container() : m_data(nullptr), m_size(0) {}

    ~my_container() {
        clear();
    }

    void add(const T& value) {
        if (m_data == nullptr) 
        {
            m_data = m_allocator.allocate(1);
        } else 
        {
            T* newData = m_allocator.allocate(m_size + 1);
            for (size_t i = 0; i < m_size; ++i) {
                m_allocator.construct(newData + i, std::move(m_data[i]));
                m_allocator.destroy(m_data + i);
            }
            m_allocator.deallocate(m_data, m_size);
            m_data = newData;
        }

        m_allocator.construct(m_data + m_size, value);
        m_size++;
    }

    void iterate() {
        for (size_t i = 0; i < m_size; ++i)
            std::cout << i << " " << m_data[i] << std::endl;
    }

    void clear() {
        if (m_data != nullptr) {
            for (size_t i = 0; i < m_size; ++i)
                m_allocator.destroy(m_data + i);
            m_allocator.deallocate(m_data, m_size);
            m_data = nullptr;
            m_size = 0;
        }
    }

private:
    T* m_data;
    size_t m_size;
    Alloc m_allocator;
};