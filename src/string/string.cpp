#include <clstl/string.h>

namespace clstl {

    string::string() : m_Length(0), m_Buffer(nullptr) {}

    string::string(const char* buffer) {

        this->m_Length = strlen(buffer);
        
        this->m_Buffer = new char[this->m_Length + 1];
        strcpy(m_Buffer, buffer);
        m_Buffer[m_Length] = 0;

    }

    string::string(const string& other) {

        this->m_Length = other.m_Length;
        this->m_Buffer = new char[m_Length + 1];
        strcpy(m_Buffer, other.m_Buffer);
        m_Buffer[m_Length] = 0;

    }

    string::~string() {
        delete[] m_Buffer;
    }

    string& string::concat(const string& other) {

        ulong newLength = other.m_Length + this->m_Length;
        char* newBuf = new char[newLength + 1];
        strcpy(newBuf, m_Buffer);
        strcpy(newBuf + m_Length, other.m_Buffer);
        newBuf[newLength] = 0;

        string* newStr = new string;
        newStr->m_Buffer = newBuf;
        newStr->m_Length = newLength;

        return *newStr;

    }

    string& string::operator+(const string& other) {
        return this->concat(other);
    }

    char& string::operator[](ulong index) {
        return m_Buffer[index];
    }

    uint strlen(const char* str) {

        uint len = 0;

        uint index = 0;
        while (char c = str[index] != 0) {

            len++;
            index++;

        }

        return len;

    }

    void strcpy(char* dest, const char* src) {

        uint index = 0;
        while (src[index] != 0) {

            dest[index] = src[index];
            index++;

        }

    }


    const char* string::c_str() const { return m_Buffer; }

}

clstl::string& operator ""_s(const char* lit, size_t) {

    clstl::string* str = new clstl::string(lit);
    return *str;

}

std::ostream& operator<<(std::ostream& stream, const clstl::string& str) {
    stream << str.c_str();
    return stream;
}