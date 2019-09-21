#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <clstl/types.h>

namespace clstl {

    template<typename T>
    class unique_ptr {

    private:
        T* m_Ptr;

    public:

        unique_ptr() : m_Ptr(nullptr) { }
        ~unique_ptr() { delete m_Ptr; }

        explicit unique_ptr(T* ptr) : m_Ptr(ptr) { }

        T* get() const { return m_Ptr; }

        T& operator[](size_t offset) { return m_Ptr[offset]; }

        unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
        unique_ptr<T>& operator=(unique_ptr<T>&&) = default;
        unique_ptr(unique_ptr<T>&&) = default;
        unique_ptr(const unique_ptr<T>&) = delete;

        T* operator->() { return m_Ptr; }
        T& operator*() { return *m_Ptr; }

    };

    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(args...));
    }

}

#endif