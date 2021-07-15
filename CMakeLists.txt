# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (main)

# Add an executable
#add_executable(main test_printf.cpp)
add_subdirectory(encrype_decrype)
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(ipc)
add_subdirectory(container)