cmake_minimum_required(VERSION 3.10)
project(UtilsTests)

# Enable testing
enable_testing()

# Collect all test source files
file(GLOB TEST_SRC "*.c")

# Create a test executable
add_executable(utils_tests ${TEST_SRC})

# Link the test executable with the utils library
target_link_libraries(utils_tests PRIVATE utils)

# Add tests to CTest
add_test(NAME UtilsTests COMMAND utils_tests "/home/madokaiii/voting_methods/votes/VoteCondorcet.csv" 10)
