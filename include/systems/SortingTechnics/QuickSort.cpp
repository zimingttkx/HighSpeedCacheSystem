#pragma once
#include <algorithm>
#include <vector>

namespace cfs {
    /**
 * 快速排序
 * 算法原理:
 * 1. 选一个「基准值」，把数组分成两堆：左边都≤基准，右边都≥基准（分区）
 * 2. 基准值会直接放到它「最终该在的位置」，不用再动了
 * 3. 对左右两堆重复上面的操作，直到所有元素都排好序
 *
 * 缺点:
 * 1. 最坏情况下时间复杂度会从O(n log n)退化成O(n²)
 * 2. 递归加分区在子数组很小的时候开销不值得 不如插入排序
 * 3. 爆递归栈
 */

    template<typename T>
    void quick_sort_basic(std::vector<T>& arr) {
        if (arr.size() < 2) return;
        // 递归处理arr 下标从0到arr.size() - 1;
        quick_sort_recursive(arr, 0, static_cast<int>(arr.size() - 1));
    }

    template<typename T>
    void quick_sort_recursive(std::vector<T>&arr, int low, int high) {
        if (low >= high) {
            return;
        }
        const T& pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivot_pos = i + 1; // 基准现在的位置 已经排好序了

        quick_sort_recursive(arr, low, pivot_pos - 1);
        quick_sort_recursive(arr, pivot_pos + 1, high);
    }
}