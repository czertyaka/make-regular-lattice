# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.20)
project(mrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mrl main.cpp arguments.cpp)

enable_testing()

add_test(no_args mrl.exe)
set_tests_properties(
    no_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(fewer_args mrl.exe 1 2)
set_tests_properties(
    fewer_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(too_much_args mrl.exe 1 2 3 4)
set_tests_properties(
    too_much_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

set(TEST_DIR "${CMAKE_SOURCE_DIR}/../test")

add_test(invalid_input_file mrl.exe "${TEST_DIR}/irregular_lattice.csv.invalid" 3 header)
set_tests_properties(
    invalid_input_file PROPERTIES
    PASS_REGULAR_EXPRESSION "input file \"${TEST_DIR}/irregular_lattice.csv.invalid\" doesn't exist"
)

add_test(invalid_last_arg mrl.exe "${TEST_DIR}/irregular_lattice.csv" 3 iNvAlIdArGuMeNt)
set_tests_properties(
    invalid_last_arg PROPERTIES
    PASS_REGULAR_EXPRESSION "third argument should be \"header\" or \"no_header\""
)

add_test(good_one_header mrl.exe "${TEST_DIR}/irregular_lattice.csv" "${TEST_DIR}/output" header)
set_tests_properties(
    good_one_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(good_one_no_header mrl.exe "${TEST_DIR}/irregular_lattice.csv" "${TEST_DIR}/output" no_header)
set_tests_properties(
    good_one_no_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(missing_header mrl.exe "${TEST_DIR}/irregular_lattice_no_header.csv" "${TEST_DIR}/regular_lattice.csv" header)
set_tests_properties(
    missing_header PROPERTIES
    PASS_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${TEST_DIR}/irregular_lattice_no_header.csv\"."
)

add_test(no_missing_header mrl.exe "${TEST_DIR}/irregular_lattice_no_header.csv" "${TEST_DIR}/regular_lattice.csv" no_header)
set_tests_properties(
    no_missing_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${TEST_DIR}/irregular_lattice_no_header.csv\"."
)

add_test(check_output mrl.exe "${TEST_DIR}/irregular_lattice.csv" "${TEST_DIR}/regular_lattice.csv" header)
set_tests_properties(
    check_output PROPERTIES
    PASS_REGULAR_EXPRESSION "regular lattice written to ${TEST_DIR}/regular_lattice.csv"
)