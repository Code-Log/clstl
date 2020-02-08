cmake_minimum_required(VERSION 3.13)
project(clstl)

enable_testing()
add_library(
    clstl 
    "src/string/string.cpp"
)

add_executable(clstl_test tests/main.cpp)
target_include_directories(clstl_test PUBLIC include)
target_link_directories(clstl_test PUBLIC build)
target_link_libraries(clstl_test clstl)

add_test(test_vector clstl_test 1)
add_test(test_unique_ptr clstl_test 2)
add_test(test_list clstl_test 3)
add_test(test_slist clstl_test 4)
add_test(test_stack clstl_test 5)
add_test(test_string clstl_test 6)

set_target_properties(
    clstl PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

target_include_directories(clstl PUBLIC include)

install(TARGETS clstl DESTINATION lib)
install(DIRECTORY include DESTINATION .)
