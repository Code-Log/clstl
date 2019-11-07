cmake_minimum_required(VERSION 3.13)
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
install(DIRECTORY include DESTINATION .)
