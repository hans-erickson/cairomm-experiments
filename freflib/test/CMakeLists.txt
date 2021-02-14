cmake_minimum_required(VERSION 3.10)

project(cmmexptest)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Cairomm REQUIRED IMPORTED_TARGET cairomm-1.0)

include_directories(${Cairomm_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
                    
set(COMMON_SRC
    main.cpp
    cmmexp-test.cpp)

add_executable(${PROJECT_NAME}
  ${COMMON_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
                      PkgConfig::Cairomm freflib gtest pthread)

