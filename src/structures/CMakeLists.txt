cmake_minimum_required(VERSION 3.20)
project(StructuresLib)

# Collect all source files
file(GLOB STRUCTURES_SRC "*.c")
file(GLOB STRUCTURES_HEADERS "*.h")

# Create a static library
add_library(structures STATIC ${STRUCTURES_SRC} ${STRUCTURES_HEADERS})

# Link with utils library
target_link_libraries(structures PUBLIC utils)

# Specify where to look for header files for this library and its dependencies
target_include_directories(structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
