cmake_minimum_required(VERSION 3.12)
project(clstl)

add_library(
    clstl "src/string/string.cpp"
)

target_include_directories(clstl PUBLIC include)