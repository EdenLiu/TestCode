# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (TEST_OPENSSL)
message(STATUS "*project ${PROJECTNAME}")
#set C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_library(LIBCRYPTO libcrypto.so REQUIRED)
#find_library(LIBPTHREAD libcrypto.so REQUIRED)
#message(STATUS "path librt : ${LIBRT}")
message(STATUS "path libcrypto : ${LIBCRYPTO}")
# Add an executable
add_executable(TEST_OPENSSL main.cpp)

#target_link_libraries MUST local AFTER add_executable, otherwise there will be error : Cannot specify link libraries for target "XXX" which is not built by this project.
target_link_libraries(TEST_OPENSSL ${LIBCRYPTO})
