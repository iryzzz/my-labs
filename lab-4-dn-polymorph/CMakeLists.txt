cmake_minimum_required (VERSION 3.8)
add_executable(lab-4-dn-polymorph
main.cpp
figure.h
point.h
point.cpp
rectangle.h
rectangle.cpp
triangle.h
triangle.cpp
trapeze.h
trapeze.cpp
ellipse.h
ellipse.cpp
)

target_link_libraries(lab-4-dn-polymorph utils_static)