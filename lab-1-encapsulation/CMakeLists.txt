cmake_minimum_required (VERSION 3.8)
add_executable(lab-1-encapsulation 
main.cpp
c-matrix.cpp
c-matrix.h
cpp-matrix.cpp
cpp-matrix.h)

target_link_libraries(lab-1-encapsulation utils_static)