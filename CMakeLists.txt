cmake_minimum_required(VERSION 3.12)
project(clstl)

add_library(
    clstl 
    "src/string/string.cpp"
    "src/collections/array_list.cpp"
)

set_target_properties(
    clstl PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

target_include_directories(clstl PUBLIC include)

install(TARGETS clstl DESTINATION lib)
install(
    FILES "include/clstl/string.h" DESTINATION "include/clstl"
)