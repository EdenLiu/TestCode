# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (Test_queue)

# Add an executable
add_executable(Test_queue test_queue.cpp)
