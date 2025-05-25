/*
 * @lc app=leetcode.cn id=213 lang=cpp
 * 动态规划（打家劫舍）
 * [213] 打家劫舍 II
 */

// @lc code=start
#include <vector>
using namespace std;

//* 题解的思路
//* 答案无非三种情况
//* 情况一：不考虑首尾元素，即考虑[1, nums.size()-2]
//* 情况二：不考虑尾元素，即考虑[0, nums.size()-2]
//* 情况三：不考虑首元素，即考虑[1, nums.size()-1]
//* 注意，情况二和情况三 都包含了情况一了，所以只考虑情况二和情况三就可以了。
//* 注意注释中的情况二情况三
class Solution2 {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int result1 = robRange(nums, 0, nums.size() - 2);   //* 情况二
        int result2 = robRange(nums, 1, nums.size() - 1);   //* 情况三
        return max(result1, result2);
    }
    //* 普通打家劫舍的逻辑
    int robRange(vector<int>& nums, int start, int end) {
        if (end == start) return nums[start];
        vector<int> dp(nums.size());
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
};

//! 错误！
//* 我的思路，用一个flag数组记录是否使用了nums[0]
//* 但是[2,2,4,3,2,5]时，dp为[2,2,6,6,8,9]，flag为[1,0,1,1,1,x]
//* 此时最优解应该为[2,3,5]
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        vector<bool> flag(nums.size(), false);
        dp[0] = nums[0];
        flag[0] = true;
        if (nums[0] > nums[1]) {
            dp[1] = nums[0];
            flag[1] = true;
        }
        else dp[1] = nums[1];
        for (int i = 2; i < nums.size(); i++) {
            if (i == nums.size() - 1) {
                if (flag[i-1] && flag[i-2]) {
                    if (nums[i] > nums[0]) {
                        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]) - nums[0];
                    }
                    else {
                        dp[i] = dp[i - 1];
                    }
                }
                else if (!flag[i-1] && flag[i-2]) {
                    if (nums[i] > nums[0]) {
                        dp[i] = max(dp[i - 2] + nums[i] - nums[0], dp[i - 1]);
                    }
                    else {
                        dp[i] = dp[i - 1];
                    }
                }
                else {
                    dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
                }
            }
            else {
                if (dp[i - 2] + nums[i] > dp[i - 1]) {
                    dp[i] = dp[i - 2] + nums[i];
                    flag[i] = flag[i - 2];
                }
                else {
                    dp[i] = dp[i - 1];
                    flag[i] = flag[i - 1];
                }
            }
        }
        return dp[nums.size() - 1];
    }
};
// @lc code=end

