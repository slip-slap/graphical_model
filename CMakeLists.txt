cmake_minimum_required(VERSION 3.5)

project(GM LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(test)
add_subdirectory(src)
