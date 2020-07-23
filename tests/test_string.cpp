#include <clstl/string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include "test_string.h"

extern std::vector<int> results;

bool naive_compare(const char* str1, const char* str2) {

    if (std::strlen(str1) != std::strlen(str2)) {
        std::cout << "Lengths not equal" << std::endl;
        std::cout << std::strlen(str1) << std::endl;
        std::cout << std::strlen(str2) << std::endl;
        return false;
    }

    bool equal = true;
    for (int i = 0; i < std::strlen(str1); i++) {
        equal = equal && (str1[i] == str2[i]);
    }

    return equal;

}

void test_string() {

    // Test operator+=
    {
        clstl::string test = "Hello World";
        test += '!';

        if (test[test.size() - 1] != '!') {
            results.emplace_back(-1);
            return;
        }

    }

    // Test substr
    {

        clstl::string test = "Hello World!";
        std::string std_test = "Hello World!";

        char* test_c = new char[5];
        std::strcpy(test_c, test.substr(1, 4));

        char* std_test_c = new char[5];
        std::strcpy(std_test_c, std_test.substr(1, 4).c_str());

        std::cout << test_c << std::endl;
        std::cout << std_test_c << std::endl;

        if (!naive_compare(test_c, std_test_c)) {
            results.emplace_back(-2);
            return;
        }

    }

    // Test operator==
    {

        clstl::string test = "Hello World!";
        clstl::string other = test;
        
        if (other != test) {
            results.emplace_back(-3);
            return;
        }

    }

}