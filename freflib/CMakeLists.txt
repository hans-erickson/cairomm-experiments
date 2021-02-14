cmake_minimum_required(VERSION 3.10)

# freflib = Frame effects library
project(freflib)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Cairomm REQUIRED IMPORTED_TARGET cairomm-1.0)

include_directories(${Cairomm_INCLUDE_DIRS})

add_library(${PROJECT_NAME} frame.cpp)

