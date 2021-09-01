include_directories("${CMAKE_SOURCE_DIR}/fast-cpp-csv-parser")
include_directories("${CMAKE_SOURCE_DIR}/mba/mba")

add_executable(mrl main.cpp arguments.cpp data.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mrl PRIVATE Threads::Threads)