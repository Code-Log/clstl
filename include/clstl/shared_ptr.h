#ifndef SHARED_PTR_H
#define SHARED_PTR_H

namespace clstl {

    template<typename T>
    class shared_ptr {

    private:
        T* m_Ptr;
        int* m_RefCount;
        bool* alive;

        shared_ptr(T* ptr, int* refCount) : m_Ptr(ptr), m_RefCount(refCount) { }

    public:

        shared_ptr() = default;

        ~shared_ptr() {

            (*m_RefCount)--;
            if (*m_RefCount <= 0) {
                delete m_Ptr;
                delete m_RefCount;
            }

        }

        shared_ptr(const shared_ptr<T>& other) {
            this->m_RefCount = other.m_RefCount;
            (*m_RefCount)++;
            this->m_Ptr = other.m_Ptr;
        }
        void operator=(const shared_ptr<T>& other) {
            this->m_RefCount = other.m_RefCount;
            (*m_RefCount)++;
            this->m_Ptr = other.m_Ptr;
        }

        T* operator->() { return m_Ptr; }

        T& operator*() { return *m_Ptr; }

        template<typename T2, typename... Args>
        friend shared_ptr<T2> make_shared(Args&&... args);

    };

    template<typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args) {
        int* refCount = new int;
        *refCount = 1;
        return shared_ptr<T>(new T(args...), refCount);
    }

}

#endif