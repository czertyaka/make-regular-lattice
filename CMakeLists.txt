# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.20)
project(mrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SOURCE_DIR "../src")
set(CMAKE_BINARY_DIR "./")

add_executable(mrl main.cpp)