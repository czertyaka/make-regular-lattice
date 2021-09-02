set(APP_CMD $<TARGET_FILE:mrl>)

set(INPUT "${TESTS_DIR}/irregular_lattice.csv")
set(INPUT_INVALID "${TESTS_DIR}/irregular_lattice.csv.invalid")
set(INPUT_NO_HEADER "${TESTS_DIR}/irregular_lattice_no_header.csv")
set(INPUT_WITH_CORNERS "${TESTS_DIR}/irregular_data_with_corners.csv")
set(INPUT_THREE_CORNERS "${TESTS_DIR}/irregular_data_three_corners.csv")
set(EMPTY_INPUT "${TESTS_DIR}/empty.csv")
set(OUTPUT "${TESTS_DIR}/regular_lattice.csv")

add_test(NAME no_args COMMAND ${APP_CMD})
set_tests_properties(
    no_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(NAME fewer_args COMMAND ${APP_CMD} 1 2)
set_tests_properties(
    fewer_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(NAME too_much_args COMMAND ${APP_CMD} 1 2 3 4)
set_tests_properties(
    too_much_args PROPERTIES
    PASS_REGULAR_EXPRESSION "invalid arguments number"
)

add_test(NAME invalid_input_file COMMAND ${APP_CMD} ${INPUT_INVALID} ${OUTPUT} header)
set_tests_properties(
    invalid_input_file PROPERTIES
    PASS_REGULAR_EXPRESSION "input file \"${INPUT_INVALID}\" doesn't exist"
)

add_test(NAME invalid_header_arg COMMAND ${APP_CMD} ${INPUT} ${OUTPUT} iNvAlIdArGuMeNt)
set_tests_properties(
    invalid_header_arg PROPERTIES
    PASS_REGULAR_EXPRESSION "third argument should be \"header\" or \"no_header\""
)

add_test(NAME missing_header COMMAND ${APP_CMD} ${INPUT_NO_HEADER} ${OUTPUT} header)
set_tests_properties(
    missing_header PROPERTIES
    PASS_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(NAME no_missing_header COMMAND ${APP_CMD} "${INPUT_NO_HEADER}" "${OUTPUT}" no_header)
set_tests_properties(
    no_missing_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "Missing column \"x\" in header of file \"${INPUT_NO_HEADER}\"."
)

add_test(NAME no_adding_corners COMMAND ${APP_CMD} "${INPUT_WITH_CORNERS}" "${OUTPUT}" header)
set_tests_properties(
    no_adding_corners PROPERTIES
    FAIL_REGULAR_EXPRESSION "adding corner node"
)

add_test(NAME adding_corners COMMAND ${APP_CMD} "${INPUT}" "${OUTPUT}" header)
set_tests_properties(
    adding_corners PROPERTIES
    PASS_REGULAR_EXPRESSION "adding corner node"
)

add_test(NAME adding_one_corner COMMAND ${APP_CMD} "${INPUT_THREE_CORNERS}" "${OUTPUT}" header)
set_tests_properties(
    adding_one_corner PROPERTIES
    PASS_REGULAR_EXPRESSION "adding corner node to input data x = -30000, y = -30000"
)

add_test(NAME no_errors_header COMMAND ${APP_CMD} ${INPUT} ${OUTPUT} header)
set_tests_properties(
    no_errors_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(NAME no_errors_no_header COMMAND ${APP_CMD} ${INPUT_NO_HEADER} ${OUTPUT} no_header)
set_tests_properties(
    no_errors_no_header PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(NAME empty_input COMMAND ${APP_CMD} ${EMPTY_INPUT} ${OUTPUT} header)
set_tests_properties(
    empty_input PROPERTIES
    PASS_REGULAR_EXPRESSION "empty input file"
)

add_test(NAME check_output COMMAND ${APP_CMD} ${INPUT} ${OUTPUT} header)
set_tests_properties(
    check_output PROPERTIES
    PASS_REGULAR_EXPRESSION "regular lattice written to ${OUTPUT}"
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${SRC_DIR})
include_directories(${MBA_DIR})
include_directories(${CSV_DIR})

add_executable(gtests gtests.cc "${SRC_DIR}/data.cpp" "${SRC_DIR}/arguments.cpp")
target_link_libraries(gtests gtest_main)

set(ZERO_PLAIN_INPUT "${TESTS_DIR}/zero-plain.csv")
set(INCLINED_PLAIN_INPUT "${TESTS_DIR}/inclined-plain.csv")
target_compile_definitions(gtests PRIVATE
    OUTPUT="${OUTPUT}"
    ZERO_PLAIN_INPUT="${ZERO_PLAIN_INPUT}"
    INCLINED_PLAIN_INPUT="${INCLINED_PLAIN_INPUT}"
)

include(GoogleTest)
gtest_discover_tests(gtests)