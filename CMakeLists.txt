cmake_minimum_required(VERSION 3.1)
project(smart_enum)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.60 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

if(MSVC)
    add_definitions("/W4")
endif()

add_executable(smart_enum main.cpp smart_enum.hpp)
