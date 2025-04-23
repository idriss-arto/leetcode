/*
 * @lc app=leetcode.cn id=674 lang=cpp
 * 动态规划
 * [674] 最长连续递增序列
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int maxCnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i-1]) {
                dp[i] = dp[i-1] + 1;
                maxCnt = max(maxCnt, dp[i]);
            }
        }
        return maxCnt;
    }
};
// @lc code=end

