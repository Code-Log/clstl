#ifndef ANY_H
#define ANY_H

#include <iostream>

#pragma once

namespace clstl {

    template<typename T>
    struct any {

    private:
        T m_Data;

    public:
        any() = default;
        any(T data) : m_Data(data) {}

        void operator=(T& data) { m_Data = data; }
        any(const any& other) : m_Data(other.m_Data) {}

        T get() const { return m_Data; }
        operator T() const { return m_Data; }

    };

}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const clstl::any<T>& data) {

    stream << data.get();
    return stream;

}

#endif