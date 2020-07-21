#ifndef ARRAY_H
#define ARRAY_H

#pragma once

#include <clstl/types.h>
#include <stdarg.h>
#include <cstring>

namespace clstl {

    template<typename T, unsigned int N>
    struct array {

    private:
        T m_Data[N];

    public:

        array() = default;

        array(T data, ...) {

            va_list arglist;
            va_start(arglist, data);

            m_Data[0] = data;
            for (unsigned int i = 1; i < N; i++) {
                m_Data[i] = va_arg(arglist, T);
            }

        }

        unsigned int size() { return N; }
        array(T* data) {
            for (int i = 0; i < N; i++) {
                m_Data[i] = data[i];
            }
        }

        void for_each(void(*func)(T&)) {

            for (unsigned int i = 0; i < this->size(); i++)
                func(this->at(i));

        }

        T& at(unsigned int index) { return m_Data[index]; }
        T& operator[](unsigned int index) { return this->at(index); }

        T* data() { return m_Data; }

        T& front() { return m_Data[0]; }
        T& back() { return m_Data[N - 1]; }
        
        void operator=(const array<T, N>& other) {
            for (int i = 0; i < N; i++)
                m_Data[i] = other.m_Data[i];
        }

    };

}

#endif