cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.27)
project(Exquisitor VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")

# Python3
find_package (Python3 COMPONENTS Interpreter Development REQUIRED)
link_directories(${Python3_LIBRARY_DIRS})
include_directories(${Python3_INCLUDE_DIRS})

# HDF5
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Project Files
include_directories(src)

add_subdirectory(src)
#add_subdirectory(tests)