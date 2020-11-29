#ifndef CLSTL_QUEUE_H
#define CLSTL_QUEUE_H

#pragma once

namespace clstl {

    template<class T, int N>
    class queue {
    private:
        T m_Data[N];
        T* m_Front;
        T* m_Back;

    public:
        queue() : m_Front(m_Data), m_Back(m_Front) {}
        queue(const queue<T, N>& other) {
            for (int i = 0; i < N; i++)
                m_Data[i] = other.m_Data[i];
            m_Front = m_Data + (other.m_Front - other.m_Data);
            m_Back = m_Data + (other.m_Back - other.m_Data);
        }

        queue<T, N>& operator=(const queue<T, N>& other) {
            *this = queue(other);
            return *this;
        }

        void push(const T& item) {

            (*m_Back) = item;
            m_Back++;
            if (m_Back > m_Data + N)
                m_Back = m_Data;

        }

        T pop() {

            T item = *m_Front;
            m_Front++;
            if (m_Front > m_Data + N)
                m_Front = m_Data;

            return item;

        }

        T& front() { return *m_Front; }
        const T& front() const { return *m_Front; }

        T& back() {
            if (m_Back - 1 < m_Data)
                return *(m_Data + N);

            return *(m_Back - 1);
        }
        const T& back() const {
            if (m_Back - 1 < m_Data)
                return *(m_Data + N);
                
            return *(m_Back - 1);
        }

        bool empty() const { return (m_Front == m_Back); }
        unsigned int size() const {

            if (m_Back < m_Front)
                return N - (m_Front - m_Back);
            else
                return (m_Back - m_Front);            

        }

        T& at(unsigned int index) {

            if (m_Front + index > m_Data + N)
                return *(m_Front + index - N);
            else
                return (*m_Front + index);

        }

        T* data(T out[N]) {
            
            for (int i = 0; i < N; i++)
                out[i] = m_Front;

        }

    };

}

#endif