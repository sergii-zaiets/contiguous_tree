cmake_minimum_required (VERSION 3.3)
project (Contiguous_tree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CodeCoverage)

# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(libs/google/benchmark)
# build tests (targets: gtest_main, gtest)
add_subdirectory(libs/google/googletest/googletest)

add_subdirectory(tests)
add_subdirectory(benchmarks)
