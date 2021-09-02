# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.16)
project(mrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
set(MBA_DIR "${CMAKE_SOURCE_DIR}/mba/mba")
set(CSV_DIR "${CMAKE_SOURCE_DIR}/fast-cpp-csv-parser")

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(${SRC_DIR})

enable_testing()
add_subdirectory(${TESTS_DIR})