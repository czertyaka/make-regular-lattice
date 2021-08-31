# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.20)
project(mrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(mrl "${SRC_DIR}/main.cpp" "${SRC_DIR}/arguments.cpp")

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

set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(INPUT "${TEST_DIR}/irregular_lattice.csv")
set(INPUT_INVALID "${TEST_DIR}/irregular_lattice.csv.invalid")
set(INPUT_NO_HEADER "${TEST_DIR}/irregular_lattice_no_header.csv")
set(OUTPUT "${TEST_DIR}/regular_lattice.csv")

add_test(invalid_input_file mrl.exe ${INPUT_INVALID} 3 header)
set_tests_properties(
    invalid_input_file PROPERTIES
    PASS_REGULAR_EXPRESSION "input file \"${INPUT_INVALID}\" doesn't exist"
)

add_test(invalid_last_arg mrl.exe ${INPUT} ${OUTPUT} iNvAlIdArGuMeNt)
set_tests_properties(
    invalid_last_arg PROPERTIES
    PASS_REGULAR_EXPRESSION "third argument should be \"header\" or \"no_header\""
)

add_test(good_one_header mrl.exe ${INPUT} ${OUTPUT} header)
set_tests_properties(
    good_one_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(good_one_no_header mrl.exe ${INPUT_NO_HEADER} ${OUTPUT} no_header)
set_tests_properties(
    good_one_no_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(missing_header mrl.exe ${INPUT_NO_HEADER} ${OUTPUT} header)
set_tests_properties(
    missing_header PROPERTIES
    PASS_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(no_missing_header mrl.exe "${INPUT_NO_HEADER}" "${OUTPUT}" no_header)
set_tests_properties(
    no_missing_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(check_output mrl.exe ${INPUT} ${OUTPUT} header)
set_tests_properties(
    check_output PROPERTIES
    PASS_REGULAR_EXPRESSION "regular lattice written to ${OUTPUT}"
)