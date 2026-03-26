cmake_minimum_required(VERSION 3.31)
project(cpp-from-scratch VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# 统一头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 顶层 header-only 库（所有模块共享）
add_library(cfs INTERFACE)
target_include_directories(cfs INTERFACE ${PROJECT_SOURCE_DIR}/include)

# 主验证入口
add_executable(cpp-from-scratch main.cpp)
target_link_libraries(cpp-from-scratch PRIVATE cfs)

# 子目录（后续按需启用）
# add_subdirectory(tests)
# add_subdirectory(benchmarks)
# add_subdirectory(examples)
