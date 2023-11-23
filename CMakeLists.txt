cmake_minimum_required(VERSION 3.27)
project(VotingMethods C)
set(CMAKE_C_STANDARD 11)
include(CTest)

# Enable additional warnings and treat all warnings as errors
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c18 -Weverything -Werror")

# Enable static analyzer during compilation
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --analyze -fsanitize=address")

# Disable specific warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-declaration-after-statement -Wno-unsafe-buffer-usage -Wno-empty-translation-unit -Wno-unused-command-line-argument")

# Define _POSIX_C_SOURCE
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_POSIX_C_SOURCE=200809L")

# Enable export of compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(src/modules)
add_subdirectory(src/structures)
add_subdirectory(src/utils)

enable_testing()

# Add Tests
add_subdirectory(test/structures)

# specify where the source files are
add_executable(VotingMethods src/main.c)

# link the executable to the libraries
target_link_libraries(VotingMethods PUBLIC modules structures utils)
