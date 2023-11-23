cmake_minimum_required(VERSION 3.20)
project(StructuresTests)

# Enable testing
enable_testing()

# Include the directory where structures library headers are located
include_directories(../../src/structures)

# Collect all test source files
file(GLOB TEST_SRC "*.c")

# Create a test executable
add_executable(structures_tests ${TEST_SRC})

# Link the test executable with the structures library
target_link_libraries(structures_tests PRIVATE structures)

# Add tests to CTest
add_test(NAME StructuresTests COMMAND structures_tests)
