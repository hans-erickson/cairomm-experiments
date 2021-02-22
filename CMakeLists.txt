cmake_minimum_required(VERSION 3.10)
project(cmmexp)

add_subdirectory(freflib)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Cairomm REQUIRED IMPORTED_TARGET cairomm-1.0)

include_directories(${Cairomm_INCLUDE_DIRS})

add_executable(hello hello.cpp)

target_link_libraries(hello PUBLIC
  PkgConfig::Cairomm
  freflib)

add_executable(graphics graphics.cpp)

target_link_libraries(graphics PUBLIC
  PkgConfig::Cairomm
  freflib)

