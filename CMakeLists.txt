cmake_minimum_required(VERSION 4.1)
project(rungo)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(rungo 
    src/main.cpp
    src/help.cpp
    src/init.cpp
    src/list.cpp
    src/run.cpp
)
