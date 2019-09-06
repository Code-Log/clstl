#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstring>
#include <clstl/types.h>

namespace clstl {

    template<typename T>
    struct array_list {

    private:
        T* m_Data;
        uint m_Count;
        uint m_Used;

        T* add_block(uint count) {

            T* newData = new T[m_Count + count];
            std::memcpy(newData, m_Data, sizeof(T) * m_Count);
            m_Count = count;

            delete[] m_Data;
            m_Data = newData;

            return m_Data;

        }

    public:
        array_list(uint count) : m_Data(new T[count]), m_Count(count), m_Used(0) {

        }

        array_list(T* data, uint count) : m_Data(new T[count]), m_Count(count), m_Used(count) {
            std::memcpy(m_Data, data, sizeof(T) * count);
        }

        array_list() : m_Data(new T[1]), m_Count(1), m_Used(0) {

        }

        array_list(const array_list<T>& other) {

            this->m_Count = other.m_Count;
            this->m_Used = other.m_Used;
            this->m_Data = new T[m_Count];

            std::memcpy(m_Data, other.m_Data, sizeof(T) * m_Used);

        }

        void push(T item) {

            if (m_Used >= m_Count)
                add_block(1);

            (*this)[m_Used] = item;
            m_Used++;

        }

        void splice(uint index, uint count) {

            for (uint i = index + count; i < m_Used; i++) {

                m_Data[i - count] = m_Data[i];

            }

            m_Used -= count;
                
        }

        void clear() {
            m_Used = 0;
        }

        T* data() {
            return m_Data;
        }

        void for_each(void(*func)(T& item)) {

            for (uint i = 0; i < m_Used; i++)
                func(m_Data[i]);

        }

        uint size() const { return m_Used; }
        uint allocated() const { return m_Count; }

        T& at(uint index) { return m_Data[index]; }
        T& operator[](uint index) { return this->at(index); }

        ~array_list() { delete[] m_Data; }

    };

}

#endif