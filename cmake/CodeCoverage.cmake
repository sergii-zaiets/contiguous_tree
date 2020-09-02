option(ENABLE_CODE_COVERAGE "Enable coverage reporting" OFF)

add_library(coverage_config INTERFACE)

if(ENABLE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  message(STATUS "[STATUS] code coverage enabled")
  # Add required flags (GCC & LLVM/Clang)

  if(ENABLE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(coverage_config INTERFACE
      -O0        # no optimization
      -g         # generate debug info
      --coverage # sets all required flags
      -fprofile-instr-generate
      -fcoverage-mapping
      -ftest-coverage
    )
  else()
    target_compile_options(coverage_config INTERFACE
      -O0        # no optimization
      -g         # generate debug info
      --coverage # sets all required flags
      -ftest-coverage
    )
  endif()


  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()

endif()

macro(link_default_target target)
  target_link_libraries(${target} coverage_config)
endmacro()