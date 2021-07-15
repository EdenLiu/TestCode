# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project TEST_MD5
project (TEST_MD5)
#find_library(SSL_LIB libssl.so REQUIRED)
#find_library(CRYPTO_LIB libcrypto.so REQUIRED)

# Add an executable
add_executable(TEST_MD5 test_MD5.cpp)
target_link_libraries( TEST_MD5
    PRIVATE 
        libssl.so
		libcrypto.so
)

# Set the project TEST_EVP
project (TEST_EVP)

# Add an executable
add_executable(TEST_EVP test_EVP.cpp)
target_link_libraries( TEST_EVP
    PRIVATE 
        libssl.so
		libcrypto.so
)

# Set the project TEST_EVP
project (TEST_EVP_BASE64)

# Add an executable
add_executable(TEST_EVP_BASE64 test_EVP_base64.cpp)
target_link_libraries( TEST_EVP_BASE64
    PRIVATE 
        libssl.so
		libcrypto.so
)