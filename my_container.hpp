#pragma once

static int c_count = 0;

template <class T, class Allocator = std::allocator<T>>
class my_container {
public:    
    my_container()
    {
        c_count++;
        m_id = c_count;        
        std::cout << "my_container(" << m_id << ")" << std::endl;        
        m_data = nullptr;
        m_size = 0;
    }

    ~my_container() 
    {
        std::cout << "~my_container(" << m_id << ")" << std::endl;        
        if (m_data != nullptr) 
        {
            for (size_t i = 0; i < m_size; ++i)
                (m_data + i)->~T();
        }
    }

    void add(const T value) 
    {
        T* new_data = m_allocator.allocate(1);
        //
        if (new_data == nullptr) 
        {
            std::cout << "allocation failed!" << std::endl;
            return;
        }
        //
        if (!m_size)
            m_data = new_data;
        //        
        *(m_data + m_size) = value;
        m_size++;
    }

    void iterate() 
    {
        for (size_t i = 0; i < m_size; ++i)
            std::cout << i << " " << *((T*)(m_data + i)) << std::endl;
    }

    std::size_t size() {
        return m_size;
    }

private:    
    int m_id;
    T* m_data;
    size_t m_size;
    Allocator m_allocator;
};