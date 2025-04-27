/*
 * @lc app=leetcode.cn id=674 lang=cpp
 * 动态规划（连续递增序列）
 * [674] 最长连续递增序列
 */

/*
 * 思路一：
 * dp[i]表示nums[i]作为连续递增子序列最后一个元素时，连续递增子序列的最大长度
 * 与300不同，这题只需比较nums[i]和nums[i-1]，即dp[i] = max(dp[i], dp[i-1] + 1);
 * 注意，计算dp[i]时，nums[i]一定在连续递增子序列中，所以dp.back()不是所求值，dp数组中的最大值才是
 * 
 ! dp[i]必须表示 “以nums[i]结尾的最长连续递增子序列” ，
 * 因为我们在做递增比较的时候，如果比较 nums[i] 和 nums[i-1] 的大小，
 * 那么两个连续递增子序列一定分别以nums[i]为结尾 和 nums[i-1]为结尾，
 * 要不然这个比较就没有意义了
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

