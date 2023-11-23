cmake_minimum_required(VERSION 3.20)

# Project's name
project(VerifyMyVote)

# Source files
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Regular executable
add_executable(verify_my_vote ${SRC_FILES})
