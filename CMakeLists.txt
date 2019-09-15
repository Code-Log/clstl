cmake_minimum_required(VERSION 3.12)
project(clstl)

add_library(
    clstl 
    "src/string/string.cpp"
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
    FILES "include/clstl/array_list.h" DESTINATION "include/clstl"
    FILES "include/clstl/array.h" DESTINATION "incude/clstl"
    FILES "include/clstl/dual.h" DESTINATION "incude/clstl"
    FILES "include/clstl/hash_map.h" DESTINATION "incude/clstl"
    FILES "include/clstl/stack.h" DESTINATION "incude/clstl"
    FILES "include/clstl/types.h" DESTINATION "incude/clstl"
    FILES "include/clstl/unique_ptr.h" DESTINATION "incude/clstl"
    FILES "include/clstl/shared_ptr.h" DESTINATION "incude/clstl"
)
