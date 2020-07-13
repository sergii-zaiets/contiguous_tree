cmake_minimum_required (VERSION 3.3)
project (Contiguous_tree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(libs/google/benchmark)

# build tests (targets: gtest_main, gtest)
add_subdirectory(libs/google/googletest/googletest)

add_executable (main main.cpp)

##############
# Unit Tests
##############

enable_testing()

add_executable(run_tests test.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_compile_options(run_tests PRIVATE --coverage)
target_link_libraries(run_tests PRIVATE --coverage gtest gtest_main )


add_test(UnitTests run_tests)
