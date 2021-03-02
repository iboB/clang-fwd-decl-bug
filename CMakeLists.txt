cmake_minimum_required(VERSION 3.10)

project(clang-fwd)

set(CMAKE_CXX_STANDARD 17)

add_executable(clang-fwd
    main.cpp
 "Session.hpp" "Session.cpp")
