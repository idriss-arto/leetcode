/*
 * @lc app=leetcode.cn id=416 lang=cpp
 * 动态规划
 * [416] 分割等和子集
 */

/*
 * 给定背包容量，判断能不能装满这个背包

 * 我的思路：
 * dp[j]表示给定数组里是否有子数组满足和为j。
 * 所以状态转移方程是if (j == nums[i] || dp[j-nums[i]] == true) dp[j] = true;
 * 最后检查dp[target]是否为true即可
 * 
 * Carl题解思路：
 * dp[j]表示容量为j的背包最多能放下的物品。
 * 按正常01背包过程计算，最后检查dp[target]是否为target
*/

//! 背包问题，不仅可以求背包能被的最大价值，还可以求这个背包是否可以装满。

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

//* dp[i]表示能否有数字加起来和刚好是true
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int& i : nums) {
            sum += i;
        }
        if (sum % 2 != 0) return false;

        vector<bool> dp(sum/2 + 1, false);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = sum/2; j >= nums[i]; j--) {    //* 每一个元素一定是不可重复放入，所以从大到小遍历
                if (j == nums[i] || dp[j-nums[i]] == true) dp[j] = true;
            }
        }

        return dp[sum/2];
    }
};

//* dp[i]表示数字加起来小于等于i的和的最大值
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;

        //* dp[i]中的i表示背包内总和
        //* 题目中说：每个数组中的元素不会超过 100，数组的大小不会超过 200
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        //* 也可以使用库函数一步求和
        //* int sum = accumulate(nums.begin(), nums.end(), 0);
        
        if (sum % 2 == 1) return false;
        int target = sum / 2;
        vector<int> dp(target + 1, 0);

        //* 开始 01背包
        for(int i = 0; i < nums.size(); i++) {
            for(int j = target; j >= nums[i]; j--) { //* 每一个元素一定是不可重复放入，所以从大到小遍历
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        
        //* 集合中的元素正好可以凑成总和target
        if (dp[target] == target) return true;
        return false;
    }
};
// @lc code=end

