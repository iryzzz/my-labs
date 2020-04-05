cmake_minimum_required (VERSION 3.8)
add_executable(lab-6-sorts 
main.cpp
sorts.h)

target_link_libraries(lab-6-sorts utils_static)