# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (data)

# Add an executable
#add_executable(main test_printf.cpp)
add_subdirectory(test_float)
add_subdirectory(test_interge)

