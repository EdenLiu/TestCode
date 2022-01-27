set(CMAKE_SYSTEM_NAME Linux)
set(Cmake_system_PROCESSOR arm)

#設置工具鏈目錄
set(TOOL_CHAIN_DIR /opt/fsl-imx-fb/4.14-sumo/sysroots)
set(TOOL_CHAIN_INCLUDE 
    ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi/usr/include
    )	
set(TOOL_CHAIN_LIB 
    ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi/usr/lib
    ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi/lib
    )

# 设置编译器位置
set(CMAKE_C_COMPILER "/opt/fsl-imx-fb/4.14-sumo/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux/arm-poky-linux-gcc")
set(CMAKE_CXX_COMPILER "/opt/fsl-imx-fb/4.14-sumo/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux/arm-poky-linux-g++")

set(CMAKE_SYSROOT ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi)
# 设置Cmake查找主路径
set(CMAKE_FIND_ROOT_PATH ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_SYSROOT}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_SYSROOT}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_SYSROOT}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -mfloat-abi=hard")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 只在指定目录下查找库文件
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 只在指定目录下查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 只在指定目录下查找依赖包
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories(
    ${TOOL_CHAIN_DIR}/cortexa7hf-neon-poky-linux-gnueabi/usr/include
    )

set(CMAKE_INCLUDE_PATH 
    ${TOOL_CHAIN_INCLUDE}
    )

set(CMAKE_LIBRARY_PATH 
    ${TOOL_CHAIN_LIB}
    )
SET(CMAKE_ARM_COMPILATION 1)
