/*
 * @lc app=leetcode.cn id=349 lang=cpp
 * 哈希
 * [349] 两个数组的交集
 */

// @lc code=start
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    // 适用于数据没有边界，离散度大的情况
    // vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    //     unordered_set<int> result_set;                                  // 存放结果，之所以用set是为了给结果集去重
    //     unordered_set<int> nums_set(nums1.begin(), nums1.end());        // 用vector的迭代器初始化unordered_set
    //     for (int num : nums2) {
    //         // 发现nums2的元素 在nums_set里又出现过
    //         if (nums_set.find(num) != nums_set.end()) {
    //             result_set.insert(num);
    //         }
    //     }
    //     return vector<int>(result_set.begin(), result_set.end());       // 用unordered_set的迭代器初始化vector
    // }

    // 适用于数据有边界的情况，运行更快，因为不用做hash运算
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set;                                      // 存放结果，之所以用set是为了给结果集去重
        int hash[1005] = {0};                                               // 默认数值为0
        for (int num : nums1) {                                             // nums1中出现的字母在hash数组中做记录
            hash[num] = 1;
        }
        for (int num : nums2) {                                             // nums2中出现话，result记录
            if (hash[num] == 1) {
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());
    }
};
// @lc code=end

