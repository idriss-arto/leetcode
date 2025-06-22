/*
 * @lc app=leetcode.cn id=198 lang=cpp
 * 动态规划（打家劫舍）
 * [198] 打家劫舍
 */

// @lc code=start
#include <vector>
using namespace std;

//* 题解的解法
//* dp[i]表示打劫下标i及之前的家最多获得的金额
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];

        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        
        return dp[nums.size() - 1];
    }
};

//* 我的解法
//* dp[i]表示打劫前i家最多获得的金额
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size()+1, 0);
        dp[0] = 0;
        dp[1] = nums[0];

        for (int i = 2; i <= nums.size(); i++) {
            dp[i] = max(dp[i-2]+nums[i-1], dp[i-1]);
        }

        return dp[nums.size()];
    }
};
// @lc code=end

