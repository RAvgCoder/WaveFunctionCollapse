cmake_minimum_required(VERSION 3.27)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)

add_executable(WaveFunctionCollapse src/main.cpp
        src/FIleParser.cpp
        headers/FileParser.h
        src/ImageFactory.cpp
        headers/ImageFactory.h
        src/Image.cpp
        headers/Image.h)
