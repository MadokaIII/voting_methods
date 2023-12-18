cmake_minimum_required(VERSION 3.10)
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
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS}-lm")

# Add compiler flags for sanitizers in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
endif()

# Export Compile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(verify_my_vote)
add_subdirectory(test)
