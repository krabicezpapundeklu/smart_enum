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
    add_definitions("-Werror -Weverything -Wno-c++98-compat-pedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_definitions("-Wall -Weffc++ -Werror -Wextra -pedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions("/Wall /WX /wd4514 /wd4710 /wd4715")
endif()

add_executable(smart_enum examples.cpp smart_enum.hpp)
