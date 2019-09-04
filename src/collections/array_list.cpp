#include <clstl/array_list.h>

namespace clstl {

    template<typename T>
    T& array_list<T>::operator[](unsigned int index) { return m_Data[index]; }

}