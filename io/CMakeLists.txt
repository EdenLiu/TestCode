# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (TEST_IO)

# Add an executable
#add_executable(main test_file_io.cpp)
add_subdirectory(file_io)
add_subdirectory(printf)