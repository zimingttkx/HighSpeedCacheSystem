# HighSpeedCacheSystem

一个基于 C++20 实现的高性能、线程安全的缓存系统，支持多种页面替换策略。

## 项目简介

HighSpeedCacheSystem 是一个从零构建的缓存中间件，旨在深入理解缓存在系统架构中的核心作用。项目从数据结构设计到多线程并发控制，完整覆盖了构建高性能缓存系统的各个关键环节。

## 核心特性

- **多种替换策略**
  - **LRU**（Least Recently Used）：最近最久未使用算法，适合时间局部性强的场景
  - **LFU**（Least Frequently Used）：最不经常使用算法，适合热点数据稳定的场景
  - **ARC**（Adaptive Replacement Cache）：自适应替换算法，自动在 LRU 和 LFU 之间寻找最优平衡

- **线程安全**
  - 基于 `std::mutex` 和 `std::shared_mutex` 的读写锁机制
  - 使用 `std::atomic` 保证计数器等操作的原子性
  - 细粒度锁设计，减少锁持有时间

- **缓存分片**
  - 将缓存划分为多个独立分片（Shard），每个分片持有独立的锁
  - 有效降低高并发场景下的锁竞争，提升系统吞吐量

- **高可用防护**
  - **缓存穿透**：空值缓存 + 布隆过滤器
  - **缓存击穿**：互斥锁防并发重建
  - **缓存雪崩**：过期时间随机化 + 预加载预热

## 目录结构

```
HighSpeedCacheSystem/
├── include/
│   └── hs_cache/           # 核心头文件
│       ├── cache.h         # 缓存统一接口
│       ├── lru_cache.h     # LRU 缓存实现
│       ├── lfu_cache.h     # LFU 缓存实现
│       ├── arc_cache.h     # ARC 缓存实现
│       ├── sharded_cache.h # 分片缓存
│       └── utils.h         # 工具函数
├── src/                    # 核心源文件
├── tests/                  # 单元测试
├── benchmarks/             # 性能基准测试
├── examples/               # 使用示例
├── CMakeLists.txt          # 构建配置
├── LICENSE                 # MIT 许可证
└── README.md
```

## 环境要求

- **编译器**：支持 C++20 的编译器（GCC 11+ / Clang 14+ / MSVC 2022+）
- **CMake**：3.31 及以上版本
- **操作系统**：Linux / macOS / Windows

## 构建方法

```bash
# 克隆仓库
git clone https://github.com/<your-username>/HighSpeedCacheSystem.git
cd HighSpeedCacheSystem

# 创建构建目录并编译
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```

## 快速示例

```cpp
#include "hs_cache/cache.h"
#include <iostream>

int main() {
    // 创建 LRU 缓存，容量为 1000
    hs_cache::LRUCache<std::string, std::string> cache(1000);

    cache.put("key1", "value1");
    auto value = cache.get("key1");

    if (value.has_value()) {
        std::cout << "key1: " << value.value() << std::endl;
    }

    return 0;
}
```

## 性能基准

> 后续补充 benchmark 数据

## 参与贡献

欢迎提交 Issue 和 Pull Request。

## 许可证

本项目基于 [MIT License](LICENSE) 开源。
