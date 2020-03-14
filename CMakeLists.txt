cmake_minimum_required(VERSION 2.6)

project(XMLParser)

enable_language(CXX)

set(CMAKE_CXX_FLAGS "-g ")

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("src")

add_executable(ParserEngine.exe "src/XMLParser.cpp"
                                "src/ContextClass.cpp"
                                "src/StateController.cpp"
                                "src/InitState.cpp"
                                "src/OpenArrow.cpp"
                                "src/Entity.cpp"
                                "src/Attribute.cpp"
                                "src/Cdata.cpp"
                                "src/Description.cpp"
                                "src/EscapeHandler.cpp"
                                "src/MiscFunctions.cpp")
