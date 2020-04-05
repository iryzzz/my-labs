cmake_minimum_required (VERSION 3.8)
add_executable(lab-2-operator-overload 
main.cpp
bin-image.cpp
bin-image.h)

target_link_libraries(lab-2-operator-overload utils_static)