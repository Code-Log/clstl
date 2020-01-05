#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <clstl/vector.h>
#include <clstl/unique_ptr.h>

std::vector<std::function<void(void)>> test_funcs;
std::vector<int> results(1);

void test_vector(void) {

    clstl::vector<int> test_vec(1);
    test_vec.emplace_back(255);

    if (test_vec[0] != 255) {
        results.emplace_back(-1);
    }

    results.emplace_back(0);

}

void* deleted_memory = nullptr;

void operator delete(void* ptr) noexcept {

    deleted_memory = ptr;
    free(ptr);

}

void test_unique_pointer(void) {

    static bool created = false;
    static bool destroyed = false;

    class Entity {

    private:
        const char* m_Name;
    
    public:
        Entity(const char* name) : m_Name(name) { created = true; }
        Entity(const Entity& other) : m_Name(other.m_Name) { }

        void printName() { std::cout << m_Name << std::endl; }

    };
    
    // Create temporary scope to test pointer auto-deletion
    void* ptr;
    {
        clstl::unique_ptr<Entity> u_ptr = clstl::make_unique<Entity>("name");
        if (!created) {
            results.emplace_back(-1);
            return;
        }
        ptr = u_ptr.getPointer();
    }

    if (deleted_memory != ptr) {
        results.emplace_back(-1);
        return;
    }

}

int main(int argc, const char** argv) {

    test_funcs.push_back(test_vector);
    test_funcs.push_back(test_unique_pointer);

    if (argc <= 1) {
        
        std::cout << "No tests run" << std::endl;
        return 0;

    } else {
        
        // Run every test according to it's number in argv
        for (int i = 1; i < argc; i++) {

            std::stringstream stream(argv[i]);
            int test_num;
            stream >> test_num;

            if (test_num >= test_funcs.size()) {
                std::cout << "Invalid test" << std::endl;
                return 0;
            }

            test_funcs[test_num]();
        
        }
        
    }

    std::vector<int> failures;
    for (int i = 0; i < results.size(); i++) {
        if (results[i] != 0) {
            std::cout << "Test " << i + 1 << " failed" << std::endl;
            failures.emplace_back(results[i]);
        }
    }

    if (failures.size() != 0) {

        std::cout << "One or more tests failed!" << std::endl;
        return -1;

    }

    return 0;

}
