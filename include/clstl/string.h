#include <ostream>
#include <clstl/types.h>
#include <memory>

namespace clstl {

    class string {

    private:
        char* m_Buffer;
        ulong m_Length;

    public:
        string();
        string(const char* buffer);
        string(const string& other);
        ~string();

        string concat(const string& other);
        string operator+(const string& other);
        char& operator[](ulong index);
        void operator=(const string& other);
        const char* c_str() const;

    };

    uint strlen(const char* str);
    void strcpy(char* dest, const char* src);

}

clstl::string& operator ""_s(const char* lit, size_t);
std::ostream& operator<<(std::ostream& stream, const clstl::string& str);