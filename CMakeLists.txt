cmake_minimum_required(VERSION 2.6)

project(XMLParser)

enable_language(CXX)

set(CMAKE_CXX_FLAGS "-g ")
add_executable(ParserEngine.exe src/XMLParser.cpp)
