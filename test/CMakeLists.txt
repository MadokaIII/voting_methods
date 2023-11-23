cmake_minimum_required(VERSION 3.20)
project(VotingMethodsTests)

# Enable testing
enable_testing()

# Add subdirectories for each set of unit tests
add_subdirectory(utils)
add_subdirectory(structures)
add_subdirectory(modules)

# Assuming VotingMethods executable is created in the src directory
# and requires a test to validate its complete functionality.

# Define the test for the VotingMethods executable
add_test(NAME VotingMethodsExecutableTest 
         COMMAND VotingMethods)
