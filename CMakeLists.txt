cmake_minimum_required(VERSION 3.4.1)

project(jsoncppdemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(jsoncpp)
add_subdirectory(src)
add_subdirectory(example)