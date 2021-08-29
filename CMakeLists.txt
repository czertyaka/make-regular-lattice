# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.20)
project(mrl)

set(CMAKE_SOURCE_DIR "../src")
set(CMAKE_BINARY_DIR "./")

add_executable(main main.cpp)