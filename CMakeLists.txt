cmake_minimum_required (VERSION 3.3)
project (Contiguous_tree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#
# compiler #defines
#_______________________________________________________________________________
add_definitions(-DBUILD_TYPE="${CMAKE_BUILD_TYPE}")
add_definitions(-DCOMPILER_NAME="${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

include(CodeCoverage)

#message('Contiguous_tree compliler used: '${CMAKE_CXX_COMPILER_ID} - ${CMAKE_CXX_COMPILER_VERSION})

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
target_compile_options(run_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(run_tests gtest gtest_main -fprofile-instr-generate -fcoverage-mapping)
add_test(UnitTests run_tests)

##############
# Benchmarks
##############

add_executable(run_benchmarks benchmark.cpp)
target_link_libraries(run_benchmarks gtest benchmark::benchmark benchmark::benchmark_main)

#llvm-profdata merge  default.profraw -o default.profdata
#llvm-cov show ./run_tests -instr-profile=default.profdata -format="html" -output-dir=.