/*
 * @lc app=leetcode.cn id=1005 lang=cpp
 *
 * [1005] K 次取反后最大化的数组和
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
//* 贪心
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        //* 首先把所有负数转为正数
        int i = 0;
        for (; i < nums.size() && k > 0; i++) {
            if (nums[i] < 0) {
                nums[i] = -nums[i];
                k--;
            }
            else {
                break;
            }
        }

        //* 如果翻转次数没用完并且剩余次数为奇数
        //! 那么重新排序
        //* 找到现在的最小正数
        if (k != 0 && k % 2 != 0) {
            //? sort(nums.begin(), nums.end());
            //! 可优化为以下式子，因为最小正数一定在原来的负数和原来的第一个非负数之间
            if (i != nums.size()) sort(nums.begin(), nums.begin() + i + 1);
            else sort(nums.begin(), nums.end());
            nums[0] = -nums[0];
            k = 0;
        }

        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return sum;
    }
};
// @lc code=end

