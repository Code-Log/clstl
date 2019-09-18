#ifndef STACK_H
#define STACK_H

#pragma once

#include <clstl/types.h>
#include <clstl/array_list.h>

namespace clstl {

    template<typename T>
    struct stack {
        
    private:
        array_list<T> m_Data;

    public:
        stack() = default;
        
        void push(const T& data) {

            m_Data.push(data);

        }

        T pop() {

            T ret = m_Data[m_Data.size() - 1];
            m_Data.splice(m_Data.size() - 1, 1);
            return ret;

        }

        T& at(size_t index) { return (*this)[index]; }
        T& operator[](size_t index) { return m_Data[index]; }

    };
    
}

#endif