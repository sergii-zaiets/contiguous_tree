cmake_minimum_required (VERSION 3.3)
project (Contiguous_tree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory (library)

add_executable (main main.cpp)
target_link_libraries (main LINK_PUBLIC trees)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/library")
