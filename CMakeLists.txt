cmake_minimum_required(VERSION 3.1)
project(smart_enum)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.60 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions("-Weverything -Wno-c++98-compat-pedantic -Wno-disabled-macro-expansion -Wno-gnu-zero-variadic-macro-arguments")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_definitions("-Wall -Weffc++ -Werror -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions("/W4")
endif()

add_executable(smart_enum main.cpp smart_enum.hpp)
