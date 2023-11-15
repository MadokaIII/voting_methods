# at the root of your project
cmake_minimum_required(VERSION 3.10)
project(VotingMethods C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-D_POSIX_C_SOURCE=200809L")

# Add subdirectories
add_subdirectory(src/data-structures)
add_subdirectory(src/utils)
add_subdirectory(src/modules)

# specify where the source files are
add_executable(VotingMethods src/main.c)

# link the executable to the libraries
target_link_libraries(VotingMethods PUBLIC DataStructures Utils Modules)
