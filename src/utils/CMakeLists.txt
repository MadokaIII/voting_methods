cmake_minimum_required(VERSION 3.10)
project(UtilsLib)

# Collect all source files
file(GLOB UTILS_SRC "*.c")
file(GLOB UTILS_HEADERS "*.h")

# Create a static library
add_library(utils STATIC ${UTILS_SRC} ${UTILS_HEADERS})

# Specify where to look for header files for this library
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
