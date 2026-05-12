#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class Vector{
   
public:
    Vector(){
        ReAlloc(2);
    }

    ~Vector(){
        ::operator delete(m_Data, m_Capacity * sizeof(T)); // This essentially just deletes the memory and doesn't call the destructor class of the objects in the memory.
        // delete[] m_Data;
      
    }

    void PushBack(const T& value){
        if(m_Size >= m_Capacity){
            ReAlloc(m_Capacity + m_Capacity/2);
        }
        m_Data[m_Size] = value;
        m_Size++;
    }

    void PushBack(T&& value){
        if(m_Size >= m_Capacity){
            ReAlloc(m_Capacity + m_Capacity/2);
        }
        m_Data[m_Size] = std::move(value);
        m_Size++;
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args){
        if(m_Size >= m_Capacity){
            ReAlloc(m_Capacity + m_Capacity/2);
        }
        new(&m_Data[m_Size]) T(std::forward<Args>(args)...); // This is the placement new operator. We are providing the actual memory we want the object to be constructed in.
        // m_Data[m_Size] = T(std::forward<Args>(args)...); This is not much different from using PushBack itself since we are creating the vector and moving it in both implementations    
        return m_Data[m_Size++];
    }

    void PopBack(){
        if(m_Size > 0){
            m_Size--;
            m_Data[m_Size].~T();
        }
    }

    void Clear(){
        for(size_t i=0;i<m_Size;i++){
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    const T& operator[](size_t index) const {
        if(index >= m_Size){
            //assert
        }
        return m_Data[index];
    }

    T& operator[](size_t index){
        if(index >= m_Size){
            //assert
        }
        return m_Data[index];
    }
    
    size_t Size() const {
        return m_Size;
    }

private:
    void ReAlloc(size_t newCapacity){
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        if(newCapacity < m_Size){
            m_Size = newCapacity;
        }

        for(size_t i = 0;i<m_Size;i++){
            newBlock[i] = std::move(m_Data[i]);
        }

        for(size_t i = 0;i<m_Size;i++){
            m_Data[i].~T();
        }

        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};