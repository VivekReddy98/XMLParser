cmake_minimum_required(VERSION 2.6)

project(XMLParser)

enable_language(CXX)

set(CMAKE_CXX_FLAGS "-g ")

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("src")

add_executable(ParserEngine.exe "src/XMLParser.cpp"
                                "src/Context_and_State_Controller.cpp"
                                "src/Init_State.cpp"
                                "src/Entity_Attrib_States.cpp"
                                "src/cdata.cpp")
