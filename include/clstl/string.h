#ifndef STRING_H
#define STRING_H

#pragma once

#include <ostream>
#include <istream>

namespace clstl {

    class string {

    private:
        char* m_Buffer;
        unsigned int m_Length;

    public:

        static const unsigned int npos = -1;

        string();
        string(const char* buffer);
        string(const string& other);
        ~string();

        string concat(const string& other) const;
        string operator+(const string& other) const;
        string substr(unsigned int pos = 0, unsigned int count = npos) const;

        char& at(unsigned int index);
        char& operator[](unsigned int index);

        void clear();

        unsigned int size() const;
        unsigned int length() const;
        unsigned int capacity() const;
        unsigned int max_length() const { return npos; }

        unsigned int find(char ch) const;
        unsigned int rfind(char ch) const;

        // Currently does nothing
        void shrink_to_fit() { }
        void reserve() { }

        void push_back(char ch);
        void pop_back();

        void operator=(const string& other);

        char& front();
        char& back();

        char* data();
        const char* c_str() const;
        
        bool operator==(const string& other) const;
        bool operator!=(const string& other) const;
        
        bool starts_with(const string& other) const;
        bool starts_with(const char* other) const;
        bool starts_with(char ch) const;

        bool ends_with(const string& other) const;
        bool ends_with(const char* other) const;
        bool ends_with(char ch) const;
        
        string& operator+=(const string& other);
        string& operator+=(const char* other);
        string& operator+=(char ch);

        operator char*() { return m_Buffer; }

        bool empty() const;

    };

}

clstl::string& operator ""_s(const char* lit, size_t size);
std::ostream& operator<<(std::ostream& stream, const clstl::string& str);

#endif