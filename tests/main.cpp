#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <memory>
#include <clstl/vector.h>
#include <clstl/unique_ptr.h>
#include <clstl/shared_ptr.h>
#include <clstl/list.h>
#include <clstl/slist.h>
#include <clstl/array.h>

#define TEST_STRING "this is a long test string with some control characters\t\n"
#define TEST_INTEGER 4e6

std::vector<std::function<void(void)>>* test_funcs;
std::vector<int> results(1);

class Entity {

private:
    const char* m_Name;

public:
    Entity(const char* name) : m_Name(name) { }
    Entity(const Entity& other) : m_Name(other.m_Name) { }

    const char* getName() { return m_Name; }

};

void test_vector(void) {

    clstl::vector<int> test_vec(1);
    test_vec.emplace_back(255);

    if (test_vec[0] != 255) {
        results.emplace_back(-1);
    }

    results.emplace_back(0);

}

void test_unique_ptr(void) {
    
    auto test_ptr = clstl::make_unique<int>(1);
    if (!(*test_ptr)) {
        results.emplace_back(-1);
        return;
    }

    auto test_ptr_entity = clstl::make_unique<Entity>("name");
    if (strcmp("name", test_ptr_entity->getName()) != 0) {
        results.emplace_back(-2);
        return;
    }

}

void test_list(void) {

    clstl::list<Entity> test_list;
    test_list.emplace_back(TEST_STRING);

    if (strcmp(test_list[0].getName(), TEST_STRING) != 0) {
        results.emplace_back(-1);
        return;
    }

}

void test_slist(void) {
    
    clstl::slist<Entity> test_list;
    test_list.emplace_back(TEST_STRING);

    if (strcmp(test_list[0].getName(), TEST_STRING) != 0) {
        results.emplace_back(-1);
        return;
    }

}

void test_array(void) {

    clstl::array<int, 100> test_arr;
    int* control_arr = new int[100];

    for (int i = 0; i < test_arr.size(); i++) {
        test_arr[i] = i;
        control_arr[i] = i;
    }

    int result = 0;
    int control_res = 0;
    for (int i = 0; i < test_arr.size(); i++) {
        result += test_arr[i];
        control_res += control_arr[i];
    }

    if (result != control_res) {
        results.emplace_back(-1);
        return;
    }

}

int main(int argc, const char** argv) {

    test_funcs = new std::vector<std::function<void(void)>>();
    test_funcs->reserve(10);

    test_funcs->push_back(test_vector);
    test_funcs->push_back(test_unique_ptr);
    test_funcs->push_back(test_list);
    test_funcs->push_back(test_slist);

    if (argc <= 1) {
        
        std::cout << "No tests run" << std::endl;
        return 0;

    } else {
        
        // Run every test according to it's number in argv
        for (int i = 1; i < argc; i++) {

            std::stringstream stream(argv[i]);
            int test_num;
            stream >> test_num;

            if (test_num >= test_funcs->size()) {
                std::cout << "Invalid test" << std::endl;
                return 0;
            }

            (*test_funcs)[test_num - 1]();
        
        }
        
    }

    std::vector<int> failures;
    for (int i = 0; i < results.size(); i++) {
        if (results[i] != 0) {
            std::cout << "Test " << i + 1 << " failed" << std::endl;
            failures.emplace_back(results[i]);
        }
    }

    std::cout << "Test results:" << std::endl;
    for (int i = 0; i < failures.size(); i++) {
        std::cout << failures[i] << std::endl;
    }

    if (failures.size() != 0) {

        std::cout << "One or more tests failed!" << std::endl;
        return -1;

    }

    return 0;

}
