
# Specify source files
file(GLOB_RECURSE LIBRARY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIBRARY_HDR ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Add library target
add_library(contiguous_tree STATIC ${LIBRARY_SRC} ${LIBRARY_HDR})

set_target_properties(contiguous_tree PROPERTIES LINKER_LANGUAGE CXX)
