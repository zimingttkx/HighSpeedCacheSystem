// HighSpeedCacheSystem - 高性能缓存系统
// 本文件为项目入口，用于基础功能验证

#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include "hs_cache/cache.h"
#include "hs_cache/lru_cache.h"
#include "hs_cache/lfu_cache.h"

using namespace hs_cache;

// ====== LRU Cache 测试 ======
void test_lru_basic() {
    std::cout << "[LRU] basic put/get... ";
    LRUCache<int, std::string> cache(3);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    assert(cache.size() == 3);
    assert(cache.get(1).value() == "one");
    assert(cache.get(2).value() == "two");
    assert(cache.get(3).value() == "three");
    std::cout << "passed" << std::endl;
}

void test_lru_eviction() {
    std::cout << "[LRU] eviction policy... ";
    LRUCache<int, int> cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    // 访问 key=1 使其变为最近使用
    cache.get(1);
    // 插入 key=4，容量已满，应淘汰最久未使用的 key=2
    cache.put(4, 40);
    assert(cache.size() == 3);
    assert(!cache.contains(2));
    assert(cache.get(2) == std::nullopt);
    assert(cache.contains(1));
    assert(cache.contains(3));
    assert(cache.contains(4));
    std::cout << "passed" << std::endl;
}

void test_lru_update() {
    std::cout << "[LRU] update existing key... ";
    LRUCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(1, 200);
    assert(cache.size() == 1);
    assert(cache.get(1).value() == 200);
    std::cout << "passed" << std::endl;
}

void test_lru_clear() {
    std::cout << "[LRU] clear... ";
    LRUCache<int, int> cache(5);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.clear();
    assert(cache.size() == 0);
    assert(!cache.contains(1));
    std::cout << "passed" << std::endl;
}

void test_lru_zero_capacity() {
    std::cout << "[LRU] zero capacity... ";
    LRUCache<int, int> cache(0);
    cache.put(1, 1);
    assert(cache.size() == 0);
    assert(cache.get(1) == std::nullopt);
    std::cout << "passed" << std::endl;
}

void test_lru_polymorphism() {
    std::cout << "[LRU] ICache polymorphism... ";
    std::unique_ptr<ICache<std::string, int>> cache = std::make_unique<LRUCache<std::string, int>>(3);
    cache->put("a", 1);
    cache->put("b", 2);
    assert(cache->get("a").value() == 1);
    assert(cache->size() == 2);
    std::cout << "passed" << std::endl;
}

// ====== LFU Cache 测试 ======
void test_lfu_basic() {
    std::cout << "[LFU] basic put/get... ";
    KLfuCache<int, std::string> cache(3);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    assert(cache.size() == 3);
    assert(cache.get(1).value() == "one");
    assert(cache.get(2).value() == "two");
    assert(cache.get(3).value() == "three");
    std::cout << "passed" << std::endl;
}

void test_lfu_eviction() {
    std::cout << "[LFU] eviction policy... ";
    KLfuCache<int, int> cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    // 多次访问 key=1，提升其频次
    cache.get(1);
    cache.get(1);
    // 插入 key=4，应淘汰频次最低且最久未使用的 key=2
    cache.put(4, 40);
    assert(cache.size() == 3);
    assert(!cache.contains(2));
    assert(cache.get(2) == std::nullopt);
    assert(cache.contains(1));
    std::cout << "passed" << std::endl;
}

void test_lfu_update() {
    std::cout << "[LFU] update existing key... ";
    KLfuCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(1, 200);
    assert(cache.size() == 1);
    assert(cache.get(1).value() == 200);
    std::cout << "passed" << std::endl;
}

void test_lfu_clear() {
    std::cout << "[LFU] clear... ";
    KLfuCache<int, int> cache(5);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.clear();
    assert(cache.size() == 0);
    assert(!cache.contains(1));
    std::cout << "passed" << std::endl;
}

void test_lfu_zero_capacity() {
    std::cout << "[LFU] zero capacity... ";
    KLfuCache<int, int> cache(0);
    cache.put(1, 1);
    assert(cache.size() == 0);
    assert(cache.get(1) == std::nullopt);
    std::cout << "passed" << std::endl;
}

void test_lfu_polymorphism() {
    std::cout << "[LFU] ICache polymorphism... ";
    std::unique_ptr<ICache<std::string, int>> cache = std::make_unique<KLfuCache<std::string, int>>(3);
    cache->put("a", 1);
    cache->put("b", 2);
    assert(cache->get("a").value() == 1);
    assert(cache->size() == 2);
    std::cout << "passed" << std::endl;
}

void test_lfu_freq_decay() {
    std::cout << "[LFU] frequency decay (K-LFU)... ";
    // 设置 max_average_num=3，低阈值方便触发降频
    KLfuCache<int, int> cache(3, 3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    // 频繁访问触发全局降频
    for (int i = 0; i < 15; ++i) {
        cache.get(1);
        cache.get(2);
        cache.get(3);
    }
    // 缓存应该仍然有效，不会崩溃
    assert(cache.contains(1));
    assert(cache.contains(2));
    assert(cache.contains(3));
    std::cout << "passed" << std::endl;
}

int main() {
    std::cout << "===== HighSpeedCacheSystem Tests =====" << std::endl;

    // LRU 测试
    test_lru_basic();
    test_lru_eviction();
    test_lru_update();
    test_lru_clear();
    test_lru_zero_capacity();
    test_lru_polymorphism();

    // LFU 测试
    test_lfu_basic();
    test_lfu_eviction();
    test_lfu_update();
    test_lfu_clear();
    test_lfu_zero_capacity();
    test_lfu_polymorphism();
    test_lfu_freq_decay();

    std::cout << std::endl << "All " << 13 << " tests passed!" << std::endl;
    return 0;
}
