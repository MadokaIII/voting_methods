cmake_minimum_required(VERSION 3.20)
project(VotingMethods C)

# Doxygen setup
find_package(Doxygen) 

# Enable testing
enable_testing()

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Normal compiler flags
add_compile_options(-D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result)

# Export Compile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(verify_my_vote)
