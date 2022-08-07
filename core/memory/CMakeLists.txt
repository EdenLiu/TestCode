# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (TEST_MEMORY)

#set C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#find_library(TEST_MEMORY librt.so REQUIRED)
#message(STATUS "path librt : ${LIBRT}")

# Add an executable
add_executable(TEST_MEMORY main.cpp nvwa/debug_new.cpp)

#target_link_libraries MUST local AFTER add_executable, otherwise there will be error : Cannot specify link libraries for target "XXX" which is not built by this project.
#target_link_libraries(TEST_MEMORY ${LIBRT})

#add_subdirectory(modifyTime)
