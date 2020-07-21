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
        unsigned int m_Count;
        unsigned int m_Used;

        T* add_block(unsigned int count) {

            T* newBuf = new T[m_Count + count];
            for (int i = 0; i < m_Used; i++)
                newBuf[i] = m_Data[i];

            delete[] m_Data;
            m_Count = m_Count + count;
            m_Data = newBuf;

            return newBuf;

        }

    public:
        vector(unsigned int count) : m_Data(new T[count]), m_Count(count), m_Used(0) {

        }

        vector(unsigned int count, T* data) : m_Data(new T[count]), m_Count(count), m_Used(count) {
            for (int i = 0; i < count; i++)
                m_Data[i] = data[i];
        }

        vector() : m_Data(new T[1]), m_Count(1), m_Used(0) { }

        vector(const vector<T>& other) {

            this->m_Count = other.m_Count;
            this->m_Used = other.m_Used;
            this->m_Data = new T[m_Count];

            for (int i = 0; i < m_Used; i++)
                m_Data[i] = other.m_Data[i];

        }

        void reserve(unsigned int count) {
            add_block(count);
        }

        void push_back(T item) {

            if (m_Used >= m_Count)
                add_block(1);

            this->m_Data[m_Used] = item;
            m_Used++;

        }

        void pop_back() {
            m_Used--;
        }

        template<typename... args_t>
        void emplace_back(args_t&&... args) {
            
            if (m_Used >= m_Count)
                add_block(1);

            new(m_Data + m_Used) T(args...);
            m_Used++;

        }

        void erase(unsigned int index, unsigned int count) {

            for (unsigned int i = index + count; i < m_Used; i++)
                m_Data[i - count] = m_Data[i];

            m_Used -= count;
                
        }

        void clear() {
            
            delete[] m_Data;
            m_Data = new T[m_Count];
            m_Used = 0;

        }

        T* data() {
            return m_Data;
        }

        T& front() { return m_Data[0]; }
        T& back() { return m_Data[m_Used - 1]; }

        void for_each(void(*func)(T& item)) {

            for (unsigned int i = 0; i < m_Used; i++)
                func(m_Data[i]);

        }

        unsigned int size() const { return m_Used; }
        unsigned int capacity() const { return m_Count; }

        void shrink_to_fit() {
            T* newBuf = new T[m_Used];
            for (int i = 0; i < m_Used; i++)
                newBuf[i] = m_Data[i];

            m_Count = m_Used;
            delete[] m_Data;
            m_Data = newBuf;
        }

        T& at(unsigned int index) { return m_Data[index]; }
        T& operator[](unsigned int index) { return this->at(index); }

        clstl::vector<T>& operator=(const clstl::vector<T>& other) {

            this->m_Count = other.m_Count;
            this->m_Used = other.m_Used;
            this->m_Data = new T[m_Count];

            for (int i = 0; i < m_Used; i++)
                m_Data[i] = other.m_Data[i];

            return *this;

        }

        ~vector() {
            delete[] m_Data;
        }

    };

}

#endif