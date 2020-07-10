cmake_minimum_required (VERSION 3.3)
project (Contiguous_tree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(libs/google/benchmark)

# build tests (targets: gtest_main, gtest)
add_subdirectory(libs/google/googletest/googletest)

add_subdirectory (library)

add_executable (main main.cpp)
target_link_libraries (main LINK_PUBLIC trees)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/library")
