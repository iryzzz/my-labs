cmake_minimum_required (VERSION 3.8)
add_executable(lab-3-st-polymorph
main.cpp
my-list.h
my-vector.h
shared-ptr.h
unique-ptr.h)

target_link_libraries(lab-3-st-polymorph utils_static)