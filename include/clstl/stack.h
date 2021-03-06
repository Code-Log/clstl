#ifndef STACK_H
#define STACK_H

#pragma once

#include <clstl/types.h>
#include <clstl/vector.h>

namespace clstl {

    template<typename T>
    struct stack {

    private:
        vector<T> m_Data;

    public:
        stack() = default;
        stack(unsigned int size) : m_Data(size) { }

        void push(const T& data) {

            m_Data.push_back(data);

        }

        T pop() {

            T ret = m_Data[m_Data.size() - 1];
            m_Data.erase(m_Data.size() - 1, 1);
            return ret;

        }

        T& at(size_t index) { return (*this)[index]; }
        T& operator[](size_t index) { return m_Data[index]; }

    };

}

#endif
