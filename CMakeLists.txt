cmake_minimum_required(VERSION 3.28)
project(DA2324_PRJ2_G28)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA2324_PRJ2_G28 main.cpp
        src/h/Parser.h
        src/cpp/Parser.cpp
        Data_Structures/Graph.h)
