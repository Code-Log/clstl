#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#pragma once

#include <clstl/shared_ptr.h>

namespace clstl {

    template<typename T>
    class weak_ptr {

    private:
        clstl::shared_ptr<T>* m_Ptr;
        bool* m_Alive;

    public:

        T* get() { return m_Ptr->get(); }
        weak_ptr() = default;

        bool is_alive() const { return *m_Alive; }
        operator bool() const { return is_alive(); }

        ~weak_ptr() { delete m_Alive; }

        weak_ptr(clstl::shared_ptr<T>& other) {

            m_Alive = new bool;
            *m_Alive = true;
            this->m_Ptr = &other;
            other.weak_ref(m_Alive);

        }

        void operator=(clstl::shared_ptr<T>& other) {

            m_Alive = new bool;
            *m_Alive = true;
            this->m_Ptr = &other;
            other.weak_ref(m_Alive);

        }

        weak_ptr(const clstl::weak_ptr<T>& other) = delete;
        void operator=(const clstl::weak_ptr<T>& other) = delete;   

        T* operator->() { return m_Ptr->get(); }
        T& operator*() { return **m_Ptr; }

    };

}

#endif