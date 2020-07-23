#include <clstl/string.h>
#include <cstring>
#include <clstl/vector.h>
#include <iostream>

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

    char& string::at(unsigned int index) { return operator[](index); }
    char& string::front() { return operator[](0); }
    char& string::back() { return operator[](m_Length - 1); }

    char* string::data() { return m_Buffer; }

    unsigned int string::size() const { return m_Length; }
    unsigned int string::length() const { return size(); }

    unsigned int string::capacity() const { return m_Length; }

    bool string::empty() const { return m_Length == 0; }

    void string::clear() {
        delete[] m_Buffer;
        m_Buffer = new char[1];
        m_Buffer[0] = 0;
        m_Length = 0;
    }

    void string::push_back(char ch) {

        m_Length++;
        char* nbuf = new char[m_Length + 1];
        std::strcpy(nbuf, m_Buffer);
        nbuf[m_Length - 1] = ch;
        delete[] m_Buffer;
        m_Buffer = nbuf;

    }

    void string::pop_back() {
        m_Buffer[m_Length - 1] = 0;
        m_Length--;
    }

    string& string::operator+=(const string& other) {
        
        unsigned int old_length = m_Length;
        
        m_Length += other.m_Length;
        char* nbuf = new char[m_Length + 1];
        
        std::strcpy(nbuf, m_Buffer);
        std::strcpy(nbuf + old_length, other.m_Buffer);
        
        delete[] m_Buffer;
        m_Buffer = nbuf;

        return *this;

    }

    string& string::operator+=(const char* other) {
        return operator+=(string(other));
    }

    string& string::operator+=(char ch) {
        push_back(ch);
        return *this;
    }

    bool string::starts_with(const string& other) const { return substr(0, other.m_Length) == other; }
    bool string::starts_with(const char* other) const { return starts_with(string(other)); }
    bool string::starts_with(char ch) const { return m_Buffer[0] == ch; }

    bool string::ends_with(const string& other) const { return substr(m_Length - other.m_Length) == other; }
    bool string::ends_with(const char* other) const { return ends_with(string(other)); }
    bool string::ends_with(char ch) const { return m_Buffer[m_Length - 1] == 0; }

    string string::substr(unsigned int pos, unsigned int count) const {

        if (count == npos)
            count = m_Length - pos;

        char* buf = new char[count + 1];
        std::memcpy(buf, m_Buffer + pos, count);
        buf[count] = 0;
        clstl::string res = buf;
        delete[] buf;
        
        return res;

    }

    unsigned int string::find(char ch) const {

        unsigned int pos = npos;
        for (int i = 0; i < m_Length; i++) 
            if (m_Buffer[i] == ch)
                pos = i;
        
        return pos;

    }

    unsigned int string::rfind(char ch) const {

        unsigned int pos = npos;
        for (int i = m_Length - 1; i >= 0; i--)
            if (m_Buffer[i] == ch)
                pos = i;

        return pos;

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