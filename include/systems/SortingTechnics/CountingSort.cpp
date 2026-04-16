// 计数排序

#include <vector>
#include <algorithm>
#include <iterator>

namespace cfs {

    /**
 * @brief 计数排序（基础版，仅支持非负整数，不稳定）
 * @tparam T 非负整数类型（如 unsigned int/int 等）
 * @param arr 待排序的数组（原地修改）
 *
 * @note 简化版实现，不支持负数，且不稳定（相同元素的相对顺序可能改变）
 * @note 适用场景：数据为非负整数，且最大值较小（如学生成绩、年龄等）
 */
    template<typename T>
    void counting_sort_basic(std::vector<T>& arr) {
        const size_t n = arr.size();
        if (n < 2) return;

        const T max_val = *std::max_element(arr.begin(), arr.end());
        const size_t count_size = static_cast<size_t>(max_val + 1);

        std::vector<size_t> count(count_size, 0); // 统计每个元素出现的次数
        for (const T& x : arr) {
            count[static_cast<size_t>(x)]++;
        }
        // 直接按照技术数组填充原数组
        size_t index = 0;
        for (size_t i = 0; i < count_size; i++) {
            while (count[i]-- > 0) {
                arr[index++] = static_cast<T>(i);
            }
        }
    }


    /**
 * @brief 计数排序（稳定版，支持负数）
 * @tparam T 整数类型（如 int/long 等，不支持浮点数/自定义类型）
 * @param arr 待排序的数组（原地修改）
 *
 * @note 适用场景：数据为整数，且数据范围（max - min）不宜过大（避免计数数组内存溢出）
 * @note 时间复杂度：O(n + k)，n为数组长度，k为数据范围
 * @note 空间复杂度：O(n + k)，使用额外的计数数组和临时数组
 * @note 稳定性：稳定（相同元素的相对顺序保持不变）
 */
template<typename T>
    void counting_sort(std::vector<T>& arr) {
    const size_t n = arr.size();
    if (n < 2) return;

    const T min_val = *std::min_element(arr.begin(), arr.end());
    const T max_val = *std::max_element(arr.begin(), arr.end());

    const T offset = min_val;
    // 数组大小 最大值减去最小值 + 1
    const size_t count_size = max_val - min_val + 1;

    std::vector<size_t> count(count_size, 0);
    for (const T& x : arr) {
        const size_t index = static_cast<size_t>(x - offset);
        count[index]++;
    }
    // 计算前缀和 表示每个元素的最终位置
    // count[i]表示小于等于i的元素个数
    for (size_t t = 1; i < count_size; i++) {
        count[i] += count[i - 1];
    }
    std::vector<T> temp(n);
    for (int i = static_cast<int>(n) - 1; i >= 0; i--) {
        const T& x = arr[static_cast<size_t>(i)];
        const  size_t index = static_cast<size_t>(x - offset);
        // 元素的最终位置等于小于等于该元素的总个数 - 1
        temp[--count[index]] = x;
    }

    arr.swap(temp); // 将排序后的临时数组高效拷贝回原数组
}


}