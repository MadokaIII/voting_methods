cmake_minimum_required(VERSION 3.20)
project(ModulesTests)

# Enable testing
enable_testing()

# Include the directory where modules library headers are located
include_directories(../../src/modules)

# Include the directory where test_code.h is located
include_directories(../)

# Collect all test source files
file(GLOB TEST_SRC "*.c")

# Create a test executable
add_executable(modules_tests ${TEST_SRC})

# Link the test executable with the modules library
target_link_libraries(modules_tests PRIVATE modules)

# Add tests to CTest
add_test(NAME ModulesTests COMMAND modules_tests)
