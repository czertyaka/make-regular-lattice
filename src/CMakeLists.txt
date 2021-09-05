include_directories("${CSV_DIR}")
include_directories("${MBA_DIR}")

add_executable(mrl main.cpp arguments.cpp data.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mrl PRIVATE Threads::Threads stdc++fs)