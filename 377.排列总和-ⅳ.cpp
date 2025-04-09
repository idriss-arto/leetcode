/*
 * @lc app=leetcode.cn id=377 lang=cpp
 * 动态规划（完全背包（求排列数））
 * [377] 排列总和 Ⅳ
 */

//* 求排列数
//! 完全背包求排列方法数没法用二维数组解

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
//* 滚动数组版本
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1, 0);
        
        dp[0] = 1;

        //! 滚动数组求排列数：必须外层遍历背包，内层遍历物品
        //* 在算dp[j] += dp[j-nums[i]];时，dp[j-nums[i]]是用所有物品求出的
        for (int j = 1; j <= target; j++) {             //* 外层遍历背包
            for (int i = 0; i < nums.size(); i++) {     //* 内层遍历物品
                //* 测试用例有两个数相加超过int范围的数据
                if (j >= nums[i] && dp[i] < INT_MAX - dp[j - nums[i]]) {
                    dp[j] += dp[j-nums[i]];
                }
            }
        }

        /* 
         ! 滚动数组求组合数：必须外层遍历物品，内层遍历背包
         * 在算dp[j] += dp[j-coins[i]];时，dp[j-nums[i]]是用下标i之前的物品求出的
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] += dp[j-coins[i]];
            }
        }
        */

        return dp[target];
    }
};

//* 二维数组版本（错误）
//! 求出来是组合数不是排列数
class Solution2 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<vector<int>> dp(nums.size() , vector<int>(target+1, 0));
        
        for (int j = nums[0]; j <= target; j += nums[0]) dp[0][j] = 1;

        for (int i = 0; i < nums.size(); i++) dp[i][0] = 1;

        for (int j = 1; j <= target; j++) {             //* 外层遍历背包
            for (int i = 0; i < nums.size(); i++) {     //* 内层遍历物品
                if(i != 0) dp[i][j] = dp[i-1][j];
                //* 测试用例有两个数相加超过int范围的数据
                if (j >= nums[i] && dp[i][j] < INT_MAX - dp[i][j - nums[i]]) {
                    dp[i][j] += dp[i][j-nums[i]];
                }
            }
        }

        return dp[nums.size()-1][target];
    }
};
// @lc code=end

//* 二维数组版本（正确）
//! 根据滚动数组版本强行推出来的，dp[i][j]失去意义
class Solution2 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<vector<int>> dp(nums.size() , vector<int>(target+1, 0));

        for (int i = 0; i < nums.size(); i++) dp[i][0] = 1;

        for (int j = 1; j <= target; j++) {             //* 外层遍历背包
            for (int i = 0; i < nums.size(); i++) {     //* 内层遍历物品
                if(i != 0) dp[i][j] = dp[i-1][j];
                //* 测试用例有两个数相加超过int范围的数据
                if (j >= nums[i] && dp[i][j] < INT_MAX - dp[nums.size()-1][j - nums[i]]) {
                    dp[i][j] += dp[nums.size()-1][j-nums[i]];
                }
            }
        }

        return dp[nums.size()-1][target];
    }
};