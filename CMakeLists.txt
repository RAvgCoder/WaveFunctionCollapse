cmake_minimum_required(VERSION 3.27)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)

add_executable(WaveFunctionCollapse src/main.cpp
        src/FIleHandler.cpp
        Header/FileHandler.h
        src/ImageContainer.cpp
        Header/ImageContainer.h)
