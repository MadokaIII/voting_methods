#!/bin/bash

# Exit on any error
set -e

# Generate Doxygen documentation
doxygen Doxyfile

# Create build directory if it doesn't exist
mkdir -p build

# Change to the build directory
cd build

# Run CMake to generate Makefile
cmake ..

# Build the project
make

# Create bin directory if it doesn't exist and move the binary to bin/
mkdir -p ../bin
mv ./src/VotingMethods ../bin/