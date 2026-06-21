cmake_minimum_required(VERSION 3.10)
project(stukshape VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 注释掉从系统查找SDL2的指令
# find_package(SDL2 REQUIRED)
# if(NOT SDL2_FOUND)
#     find_package(SDL2 QUIET)
# endif()

# 从源码编译SDL2
add_subdirectory(src/external/SDL2)

# SDL2生成的头文件目录需要在源码目录之前
include_directories(BEFORE ${CMAKE_BINARY_DIR}/src/external/SDL2/include)
include_directories(src)
include_directories(src/external/SDL2/include)

add_executable(stukshape main.cpp src/stukshape.cpp)

target_link_libraries(stukshape SDL2main SDL2)