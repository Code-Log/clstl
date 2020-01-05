#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <cstring>
#include <clstl/types.h>

namespace clstl {

    template<typename T>
    struct vector {

    private:
        T* m_Data;
        size_t m_Count;
        size_t m_Used;

        T* add_block(size_t count) {

            T* newData = (T*)new char[sizeof(T) * (m_Count + count)];
            std::memcpy(newData, m_Data, sizeof(T) * m_Used);
            m_Count = count;

            delete[] m_Data;
            m_Data = newData;

            return m_Data;

        }

    public:
        vector(size_t count) : m_Data((T*)new char[sizeof(T) * count]), m_Count(count), m_Used(0) {

        }

        vector(T* data, size_t count) : m_Data((T*)new char[sizeof(T) * count]), m_Count(count), m_Used(count) {
            std::memcpy(m_Data, data, sizeof(T) * count);
        }

        vector() : m_Data((T*)new char[sizeof(T)]), m_Count(1), m_Used(0) {

        }

        vector(const vector<T>& other) {

            this->m_Count = other.m_Count;
            this->m_Used = other.m_Used;
            this->m_Data = (T*)new char[sizeof(T) * m_Count];

            std::memcpy(m_Data, other.m_Data, sizeof(T) * m_Used);

        }

        void reserve(size_t count) {
            add_block(count);
        }

        void push_back(T item) {

            if (m_Used >= m_Count)
                add_block(1);

            this->m_Data[m_Used] = item;
            m_Used++;

        }

        template<typename... args_t>
        void emplace_back(args_t&&... args) {
            
            if (m_Used >= m_Count)
                add_block(1);

            // Construct object in-place
            new(m_Data + m_Used) T(args...);
            m_Used++;

        }

        void splice(size_t index, size_t count) {

            for (size_t i = index + count; i < m_Used; i++) {

                m_Data[i - count] = m_Data[i];

            }

            m_Used -= count;
                
        }

        /*
            Hard clear reallocates the
            underlying storage
        */
        void clear(bool hard_clear = false) {
            
            if (hard_clear) {

                delete[] m_Data;
                m_Data = (T*)new char[sizeof(T) * m_Count];

            }
            m_Used = 0;

        }

        T* data() {
            return m_Data;
        }

        // Standard clstl iterator (Not standard... I know!)
        void for_each(void(*func)(T& item)) {

            for (size_t i = 0; i < m_Used; i++)
                func(m_Data[i]);

        }

        // Returns the amount of items inserted into
        // the vector
        size_t size() const { return m_Used; }
        size_t allocated() const { return m_Count; } // Returns the integer allocated space

        T& at(size_t index) { return m_Data[index]; } // I'm not explaining this...
        T& operator[](size_t index) { return this->at(index); } // Same as this->at(index);

        ~vector() { delete[] m_Data; }

    };

}

#endif