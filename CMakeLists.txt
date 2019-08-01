cmake_minimum_required(VERSION 3.14)
project(patchtool)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(patchtool
        basic_structs.cpp
        basic_structs.h
        BugMod.cpp
        Commit.cpp
        Parser.cpp
        Parser.h
        test.cpp  Parser.cpp Parser.h)
#        Playground.cpp)
