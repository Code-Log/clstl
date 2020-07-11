#include <clstl/string.h>
#include <cstring>

namespace clstl {

    string::string() : m_Length(0), m_Buffer(new char[1]) { m_Buffer[0] = 0; }

    string::string(const char* buffer) {

        this->m_Length = std::strlen(buffer);
        this->m_Buffer = new char[this->m_Length + 1];
        
        std::strcpy(m_Buffer, buffer);
        m_Buffer[m_Length] = 0;

    }

    string::string(const string& other) {

        this->m_Length = other.m_Length;
        this->m_Buffer = new char[m_Length + 1];
        std::memcpy(this->m_Buffer, other.m_Buffer, this->m_Length + 1);
        m_Buffer[m_Length] = 0;

    }

    const char* string::c_str() const { return m_Buffer; }

    string::~string() {
        if (m_Buffer)
            delete[] m_Buffer;
    }

    string string::concat(const string& other) const {

        clstl::string newstr;
        unsigned int newlength = m_Length + other.m_Length;
        newstr.m_Buffer = new char[newlength + 1];
        std::strcpy(newstr.m_Buffer, m_Buffer);
        std::strcat(newstr.m_Buffer, other.m_Buffer);
        newstr.m_Length = newlength;

        return newstr;

    }

    string string::operator+(const string& other) const {
        return this->concat(other);
    }

    char& string::operator[](unsigned int index) {
        return m_Buffer[index];
    }

    void string::operator=(const string& other) {

        this->m_Length = other.m_Length;
        this->m_Buffer = new char[m_Length + 1];
        std::memcpy(this->m_Buffer, other.m_Buffer, this->m_Length + 1);
        m_Buffer[m_Length] = 0;

    }

    bool string::operator==(const string& other) const {

        return std::strcmp(this->m_Buffer, other.m_Buffer) == 0;

    }

    bool string::operator!=(const string& other) const {
        return !(this->operator==(other));
    }

}

clstl::string& operator ""_s(const char* lit, size_t) {

    clstl::string* str = new clstl::string(lit);
    return *str;

}

std::ostream& operator<<(std::ostream& stream, const clstl::string& str) {
    stream << str.c_str();
    return stream;
}