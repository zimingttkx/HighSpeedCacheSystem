cmake_minimum_required(VERSION 3.31)
project(HighSpeedCacheSystem VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# 头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 缓存库
add_library(hs_cache
    src/cache.cpp
    src/lru_cache.cpp
    src/lfu_cache.cpp
    src/arc_cache.cpp
    src/sharded_cache.cpp
)

target_include_directories(hs_cache PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 示例可执行文件
add_executable(HighSpeedCacheSystem main.cpp)
target_link_libraries(HighSpeedCacheSystem PRIVATE hs_cache)

# 子目录（测试、基准、示例在各自 CMakeLists 中配置）
# add_subdirectory(tests)
# add_subdirectory(benchmarks)
# add_subdirectory(examples)
