#include <clstl/string.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include "test_string.h"

extern std::vector<int> results;

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

        if (test.substr(2, 4) != clstl::string(std_test.substr(2, 4).c_str())) {
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

    {

        std::ifstream fs("test.txt");

        clstl::string line;
        while (getline(fs, line))
            std::cout << line << std::endl;

        fs.close();

    }

}