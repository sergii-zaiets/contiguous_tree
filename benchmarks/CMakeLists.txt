option(ENABLE_BENCHMARKS "Enable benchmarks" ON)

if(ENABLE_BENCHMARKS)

    add_executable(run_benchmarks benchmark.cpp)
    target_link_libraries(run_benchmarks gtest benchmark::benchmark benchmark::benchmark_main)
    target_include_directories(run_benchmarks PRIVATE "${CMAKE_SOURCE_DIR}/include")

endif()