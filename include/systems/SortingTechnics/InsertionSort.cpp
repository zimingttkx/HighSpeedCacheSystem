#pragma once
#include <algorithm>
#include <vector>

namespace cfs {
    /**
 * 插入排序实现
 *
 * 算法原理：
 * 1. 将数组分为已排序区和未排序区
 * 2. 初始时，已排序区只包含第一个元素
 * 3. 依次将未排序区的元素插入到已排序区的适当位置
 *
 * 时间复杂度：
 * - 最好情况：O(n) - 数组已经有序
 * - 最坏情况：O(n²) - 数组逆序
 * - 平均情况：O(n²)
 *
 * 空间复杂度：O(1) - 原地排序
 */
    template<typename T>
    void insertion_sort(std::vector<T>& arr) {
        size_t n = arr.size();
        if (n < 2) return;

        for (size_t i = 1; i < n; i++) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // 优化方向 主要是使用move避免了拷贝
    // 不太了解move可以学习下左值引用和右值引用
    template<typename T>
    void insertion_sort_optimized(std::vector<T>& arr) {
        size_t n = arr.size();
        if (n < 2) return;

        for (size_t i = 1; i < n; i++) {
            T key = std::move(arr[i]);
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = std::move(arr[j]);
                j--;
            }
            arr[j + 1] = std::move(key);
        }
    }
}