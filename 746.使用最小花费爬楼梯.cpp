/*
 * @lc app=leetcode.cn id=746 lang=cpp
 * 动态规划
 * [746] 使用最小花费爬楼梯
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> sum(n + 1);
        sum[0] = 0;
        sum[1] = 0;
        for (int i = 2; i <= n; i++) {
            sum[i] = min(sum[i-2] + cost[i-2], sum[i-1] + cost[i-1]);
        }
        return sum[n];
    }
};

//* 空间复杂度优化版本
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int dp0 = 0;
        int dp1 = 0;
        for (int i = 2; i <= cost.size(); i++) {
            int dpi = min(dp1 + cost[i - 1], dp0 + cost[i - 2]);
            dp0 = dp1;
            dp1 = dpi;
        }
        return dp1;
    }
};
// @lc code=end

