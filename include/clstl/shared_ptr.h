#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <clstl/vector.h>

namespace clstl {

    template<typename T>
    class shared_ptr {

    private:
        T* m_Ptr;
        int* m_RefCount;
        clstl::vector<bool*> m_AliveRefs;

        shared_ptr(T* ptr, int* refCount) : m_Ptr(ptr), m_RefCount(refCount), m_AliveRefs(2) { }

    public:

        shared_ptr() = default;

        ~shared_ptr() {

            (*m_RefCount)--;
            // std::cout << "Destroying " << this << "\nRef count: " << *m_RefCount << std::endl;

            if (*m_RefCount <= 0) {

                // std::cout << "Destroying pointer" << std::endl;
                delete m_RefCount;
                delete m_Ptr;

                m_AliveRefs.for_each([](bool*& item) { *item = false; });

            }

        }

        shared_ptr(const shared_ptr<T>& other) {

            this->m_RefCount = other.m_RefCount;
            (*m_RefCount)++;

            this->m_Ptr = other.m_Ptr;

        }

        T* get() const { return m_Ptr; }

        void operator=(const shared_ptr<T>& other) {

            this->m_RefCount = other.m_RefCount;
            (*m_RefCount)++;
            
            this->m_Ptr = other.m_Ptr;

        }

        void weak_ref(bool* ref) { m_AliveRefs.push_back(ref); }

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
