/*
 * @lc app=leetcode.cn id=136 lang=cpp
 * 技巧，位运算
 * [136] 只出现一次的数字
 */

/*
 * 相同的数异或为0
 * 0和任何数x异或结果为x
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

