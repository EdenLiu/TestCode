# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (TEST_PRINTF)

# Add an executable
add_executable(TEST_PRINTF test_printf.cpp)
