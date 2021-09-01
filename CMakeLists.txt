# MRL - make regular lattice project
cmake_minimum_required(VERSION 3.16)
project(mrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories("${CMAKE_SOURCE_DIR}/fast-cpp-csv-parser")
include_directories("${CMAKE_SOURCE_DIR}/mba/mba")

add_executable(mrl "${SRC_DIR}/main.cpp" "${SRC_DIR}/arguments.cpp")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mrl PRIVATE Threads::Threads)

enable_testing()

if(UNIX)
    set(APP_CMD "mrl")
elseif(WIN32)
    set(APP_CMD "mrl.exe")
endif()

add_test(no_args ${APP_CMD})
set_tests_properties(
    no_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(fewer_args ${APP_CMD} 1 2)
set_tests_properties(
    fewer_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(too_much_args ${APP_CMD} 1 2 3 4)
set_tests_properties(
    too_much_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(INPUT "${TEST_DIR}/irregular_lattice.csv")
set(INPUT_INVALID "${TEST_DIR}/irregular_lattice.csv.invalid")
set(INPUT_NO_HEADER "${TEST_DIR}/irregular_lattice_no_header.csv")
set(OUTPUT "${TEST_DIR}/regular_lattice.csv")

add_test(invalid_input_file ${APP_CMD} ${INPUT_INVALID} 3 header)
set_tests_properties(
    invalid_input_file PROPERTIES
    PASS_REGULAR_EXPRESSION "input file \"${INPUT_INVALID}\" doesn't exist"
)

add_test(invalid_header_arg ${APP_CMD} ${INPUT} ${OUTPUT} iNvAlIdArGuMeNt)
set_tests_properties(
    invalid_header_arg PROPERTIES
    PASS_REGULAR_EXPRESSION "third argument should be \"header\" or \"no_header\""
)

add_test(missing_header ${APP_CMD} ${INPUT_NO_HEADER} ${OUTPUT} header)
set_tests_properties(
    missing_header PROPERTIES
    PASS_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(no_missing_header ${APP_CMD} "${INPUT_NO_HEADER}" "${OUTPUT}" no_header)
set_tests_properties(
    no_missing_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(no_errors_header ${APP_CMD} ${INPUT} ${OUTPUT} header)
set_tests_properties(
    no_errors_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(no_errors_no_header ${APP_CMD} ${INPUT_NO_HEADER} ${OUTPUT} no_header)
set_tests_properties(
    no_errors_no_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(check_output ${APP_CMD} ${INPUT} ${OUTPUT} header)
set_tests_properties(
    check_output PROPERTIES
    PASS_REGULAR_EXPRESSION "regular lattice written to ${OUTPUT}"
)