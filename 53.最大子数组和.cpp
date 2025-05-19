/*
 * @lc app=leetcode.cn id=53 lang=cpp
 * 贪心，动态规划(连续子序列)
 * [53] 最大子数组和
 */

/*
 * 两个思路，动态规划和贪心
 * 
 * 动态规划思路：
 * dp[i]：包括下标i（以nums[i]为结尾）的最大连续子序列和为dp[i]。
 * 
 * dp[i]只有两个方向可以推出来：
 * dp[i - 1] + nums[i]，即：nums[i]加入当前连续子序列和
 * nums[i]，即：从头开始计算当前连续子序列和
 * 一定是取最大的，所以dp[i] = max(dp[i - 1] + nums[i], nums[i]);
 * 
 * 
 * 贪心思路：
 * 局部最优：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数加上下一个元素 “连续和”只会越来越小。
 * 全局最优：选取最大“连续和”
 * 局部最优的情况下，并记录最大的“连续和”，可以推出全局最优。

 * 从代码角度上来讲：遍历 nums，从头开始用 sum 累积，如果 sum 一旦加上 nums[i]变为负数，
 * 那么就应该从 nums[i+1] 开始从 0 累积 sum 了，因为已经变为负数的 count，只会拖累总和。
*/

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
/* 
 * 动态规划
 * 思路：
 * dp[i]：包括下标i（以nums[i]为结尾）的最大连续子序列和为dp[i]。
 * 
 * dp[i]只有两个方向可以推出来：
 * dp[i - 1] + nums[i]，即：nums[i]加入当前连续子序列和
 * nums[i]，即：从头开始计算当前连续子序列和
 * 一定是取最大的，所以dp[i] = max(dp[i - 1] + nums[i], nums[i]);
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int result = dp[0];

        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);  //* 状态转移公式
            if (dp[i] > result) result = dp[i];         //* result 保存dp[i]的最大值
        }
        return result;
    }
};

/* 
 * Carl贪心
 * 思路：
 * 局部最优：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数加上下一个元素 “连续和”只会越来越小。
 * 全局最优：选取最大“连续和”
 * 局部最优的情况下，并记录最大的“连续和”，可以推出全局最优。

 * 从代码角度上来讲：遍历 nums，从头开始用 sum 累积，如果 sum 一旦加上 nums[i]变为负数，
 * 那么就应该从 nums[i+1] 开始从 0 累积 sum 了，因为已经变为负数的 sum，只会拖累总和。
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum > result) {         //* 取区间累计的最大值（相当于不断确定最大子序终止位置）
                result = sum;
            }
            if (sum <= 0) sum = 0;      //* 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
        }
        return result;
    }
};

//* 我的解法，虽然过了，但太麻烦，没体现贪心的好处
class Solution {
public:
    
    int myMaxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int sum = 0;
        int now = 0;
        int index = 0;
        
        //* 先找到第一个正值
        for (; index < nums.size() && nums[index] <= 0; index++){           //! 不能写成nums[index] <= 0 && index < nums.size()，会越界！
            result = result > nums[index] ? result : nums[index];
        };

        //* 特殊情况处理：数组里全是负值
        if (index == nums.size()) return result;

        for (int i = index; i < nums.size(); i++) {
            if (nums[i] >= 0) {
                sum += nums[i];
                continue;
            }
            else {
                //* 先记录现在的结果
                result = result > sum ? result : sum;

                //* 统计连续负值的总和
                now = 0;
                while (i < nums.size() && nums[i] < 0) {
                    now += nums[i];
                    i++;
                }

                if (i == nums.size()) {
                    break;
                }
                else {
                    //* 判断当前连续和是否为正
                    if (sum + now >= 0) {
                        sum += nums[i] + now;
                        continue;
                    }
                    else {
                        sum = nums[i];
                    }
                }
            }
        }
        result = result > sum ? result : sum;
        return result;
    }
};
// @lc code=end

