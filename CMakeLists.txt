cmake_minimum_required(VERSION 3.14)
project(a5_connect_4)

set(CMAKE_CXX_STANDARD 14)

file(GLOB a4_proj "*.h" "*.cpp")

add_executable(a5_connect_4 ${a4_proj} Node.h Node.cpp coord.h)