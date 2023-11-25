cmake_minimum_required(VERSION 3.20)
project(UtilsTests)

# Enable testing
enable_testing()

# Include the directory where utils library headers are located
include_directories(../../src/utils)

# Include the directory where test_code.h is located
include_directories(../)

# Collect all test source files
file(GLOB TEST_SRC "*.c")

# Create a test executable
add_executable(utils_tests ${TEST_SRC})

# Link the test executable with the utils library
target_link_libraries(utils_tests PRIVATE utils)

# Add tests to CTest
add_test(NAME UtilsTests COMMAND utils_tests)
