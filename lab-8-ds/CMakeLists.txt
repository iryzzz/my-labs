cmake_minimum_required (VERSION 3.8)
add_executable(lab-8-ds
main.cpp
ordered-vector.h
unordered-set.h
ordered-set.h)

target_link_libraries(lab-8-ds utils_static)