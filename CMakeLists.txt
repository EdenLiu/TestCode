# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name

# Add an executable

project (main)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
# Add an executable
add_subdirectory(encrype_decrype)
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(ipc)
add_subdirectory(container)
add_subdirectory(assemebly_language)
add_subdirectory(bit_operate)
add_subdirectory(data)
add_subdirectory(openssl)
