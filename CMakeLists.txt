# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project(TMP CXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options(-Wall -Wextra -Wpedantic)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options(/W4 /D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory ("libutils")
add_subdirectory ("lab-1-encapsulation")
add_subdirectory ("lab-2-operator-overload")
add_subdirectory ("lab-3-st-polymorph")
add_subdirectory ("lab-4-dn-polymorph")
add_subdirectory ("lab-6-sorts")
add_subdirectory ("lab-8-ds")