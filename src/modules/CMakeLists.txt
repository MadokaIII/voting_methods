cmake_minimum_required(VERSION 3.20)
project(ModulesLib)

# Collect all source files
file(GLOB MODULES_SRC "*.c")
file(GLOB MODULES_HEADERS "*.h")

# Create a static library
add_library(modules STATIC ${MODULES_SRC} ${MODULES_HEADERS})

# Link with structures and utils libraries
target_link_libraries(modules PUBLIC structures)

# Specify where to look for header files for this library and its dependencies
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
