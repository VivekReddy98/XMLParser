cmake_minimum_required(VERSION 2.6)

project(xml)

set(DCMAKE_BUILD_TYPE "Debug")

set(CMAKE_C_COMPILER "/usr/bin/clang")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(CMAKE_CXX_DEBUGGER "/usr/bin/lldb")

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(xml.exe src/main.cpp)
