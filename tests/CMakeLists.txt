option(ENABLE_TESTS "Enable tests" ON)

if(ENABLE_TESTS)

    enable_testing()

    add_executable(run_tests test.cpp)
    link_default_target(run_tests)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(run_tests gtest gtest_main)
    add_test(UnitTests run_tests)

endif()