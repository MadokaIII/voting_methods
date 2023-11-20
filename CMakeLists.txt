cmake_minimum_required(VERSION 3.10)
project(VotingMethods C)
set(CMAKE_C_STANDARD 11)

# Set compiler flags for Clang
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  # Enable additional warnings and treat all warnings as errors
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c18 -Weverything -Werror")

  # Enable static analyzer during compilation
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --analyze -fsanitize=address")

  # Disable specific warnings if necessary
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-declaration-after-statement -Wno-unsafe-buffer-usage -Wno-empty-translation-unit -Wno-unused-command-line-argument")
endif()

# Define _POSIX_C_SOURCE
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_POSIX_C_SOURCE=200809L")

# Enable export of compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(src/structures)
add_subdirectory(src/utils)
add_subdirectory(src/modules)

# specify where the source files are
add_executable(VotingMethods src/main.c)

# link the executable to the libraries
# Ensure these are the correct library names as defined in the subdirectories
target_link_libraries(VotingMethods PUBLIC structures utils modules)
