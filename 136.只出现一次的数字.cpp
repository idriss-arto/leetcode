/*
 * @lc app=leetcode.cn id=136 lang=cpp
 * 技巧，位运算
 * [136] 只出现一次的数字
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (auto& num : nums) {
            result ^= num;
        }
        return result;
    }
};
// @lc code=end

