# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (core)

# Add an executable
add_subdirectory(time)
add_subdirectory(thread)
add_subdirectory(memory)
