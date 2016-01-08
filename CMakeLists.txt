cmake_minimum_required(VERSION 3.1)
project(smart_enum)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.60 QUIET)

if(Boost_FOUND)
    message("Using system Boost (${Boost_INCLUDE_DIRS})")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message("Using included Boost")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions("-Werror -Weverything -Wno-c++98-compat-pedantic -Wno-disabled-macro-expansion -Wno-gnu-zero-variadic-macro-arguments")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_definitions("-Wall -Weffc++ -Werror -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions("/W4 /WX")
endif()

add_executable(smart_enum examples.cpp smart_enum.hpp)
