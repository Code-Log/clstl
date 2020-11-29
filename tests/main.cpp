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
#include <clstl/hash_map.h>
#include <clstl/stack.h>
#include <clstl/string.h>
#include <clstl/queue.h>
#include "test_string.h"

#define TEST_STRING_LONG "this is a long test string with some control characters\t\n"
#define TEST_STRING_SHORT "short_string__"
#define TEST_INTEGER 4e6

#define fail_if(x, y) if (x) { results.emplace_back(y); return; }

std::vector<std::function<void(void)>>* test_funcs;
std::vector<int> results(1);

class Entity {

private:
    std::string m_Name;
    int* stuff;

public:
    Entity() : stuff(new int) { }
    Entity(const char* name) : m_Name(name), stuff(new int) { }
    Entity(const Entity& other) : m_Name(other.m_Name), stuff(new int) {
        *stuff = *other.stuff;
    }

    ~Entity() {
        std::cout << "Entity " << m_Name << " deleted!" << std::endl;
        delete stuff;
    }

    Entity& operator=(const Entity& other) {
        stuff = new int;
        *stuff = *other.stuff;
        m_Name = other.m_Name;
        return *this;
    }

    std::string getName() const { return m_Name; }

};

template<typename T>
void print_vec(clstl::vector<T>& v) {

    std::cout << "[" << v[0];
    for (int i = 1; i < v.size(); i++) {
        std::cout << "," << v[i];
    }
    std::cout << "]" << std::endl;

}

std::ostream& operator<<(std::ostream& stream, const Entity& e) {
    stream << e.getName();
    return stream;
}

void test_vector(void) {

    {
        clstl::vector<int> test_vec(1);
        test_vec.emplace_back(255);

        if (test_vec[0] != 255) {
            results.emplace_back(-1);
        }
    }

    {
        clstl::vector<int> test_vec(100);
        for (int i = 0; i < 100; i++)
            test_vec.push_back(i);

        test_vec.erase(11, 10);
        if (test_vec[11] != 21) {
            print_vec(test_vec);
            results.emplace_back(-2);
        }
    }

    {

        clstl::vector<Entity> test_vec(1);
        test_vec.emplace_back("Hi");
        test_vec.emplace_back("world");
        print_vec(test_vec);

        test_vec.pop_back();

        print_vec(test_vec);

    }

    {
        std::cout << "--" << std::endl;
        auto ptr1 = new clstl::vector<Entity>(1);
        auto ptr2 = new clstl::vector<Entity>(1);

        ptr1->emplace_back("Hello");

        *ptr2 = *ptr1;
        delete ptr1;

        print_vec(*ptr2);
        delete ptr2;

    }

    clstl::string str1 = TEST_STRING_LONG;
    clstl::string str2 = TEST_STRING_SHORT;
    {
        clstl::vector<clstl::string> str_vec;
        str_vec.push_back(str1);
        str_vec.push_back(str2);
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
    if (strcmp("name", test_ptr_entity->getName().c_str()) != 0) {
        results.emplace_back(-2);
        return;
    }

}

void test_list(void) {

    clstl::list<Entity> test_list;
    test_list.emplace_back(clstl::string(TEST_STRING_LONG));

    if (strcmp(test_list[0].getName().c_str(), TEST_STRING_LONG) != 0) {
        results.emplace_back(-1);
        return;
    }

}

void test_slist(void) {
    
    clstl::slist<Entity> test_list;
    test_list.emplace_back(TEST_STRING_SHORT);

    if (strcmp(test_list[0].getName().c_str(), TEST_STRING_SHORT) != 0) {
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

void test_hash_map(void) {

    clstl::hash_map<int, char> test_map;
    test_map.add(1, 'a');
    test_map.add(2, 'b');

    if (test_map.get(1) != 'a') {
        results.emplace_back(-1);
        return;
    }

    test_map.remove(1);
    
    if (test_map.get(1)) {
        results.emplace_back(-2);
        return;
    }

}

void test_stack(void) {

    clstl::stack<int> test_s;
    test_s.push(3);
    test_s.push(4);

    if (test_s.pop() != 4) {
        results.emplace_back(-1);
        return;
    }

}

void test_queue(void) {

    clstl::queue<int, 3> test_q;
    test_q.push(3);
    test_q.push(4);
    test_q.push(6);

    fail_if(test_q.pop() != 3, -1);
    fail_if(test_q.size() != 2, -2);

}

int main(int argc, const char** argv) {

    test_funcs = new std::vector<std::function<void(void)>>();
    test_funcs->reserve(10);

    test_funcs->push_back(test_vector);
    test_funcs->push_back(test_unique_ptr);
    test_funcs->push_back(test_list);
    test_funcs->push_back(test_slist);
    test_funcs->push_back(test_stack);
    test_funcs->push_back(test_string);
    test_funcs->push_back(test_queue);

    if (argc <= 1) {
        
        std::cout << "No tests run" << std::endl;
        return 0;

    } else {
        
        // Run every test according to it's number in argv
        for (int i = 1; i < argc; i++) {

            std::stringstream stream(argv[i]);
            int test_num;
            stream >> test_num;

            if (test_num > test_funcs->size()) {
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

    } else {
        
        std::cout << "All tests passed" << std::endl;

    }

    return 0;

}
