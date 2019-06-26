
# Specify source files
file(GLOB_RECURSE LIBRARY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIBRARY_HDR ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Add library target
add_library(trees STATIC ${LIBRARY_SRC} ${LIBRARY_HDR})

set_target_properties(trees PROPERTIES LINKER_LANGUAGE CXX)
