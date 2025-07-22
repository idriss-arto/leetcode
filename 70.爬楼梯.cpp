/*
 * @lc app=leetcode.cn id=70 lang=cpp
 * 动态规划
 * [70] 爬楼梯
 */

// @lc code=start
#include <vector>
using namespace std;

//* 普通版本
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;       //* 注意特殊情况处理
        vector<int> dp(n+1, 0);

        dp[1] = 1;
        dp[2] = 2;

        //* 注意这里从3开始
        for (int i = 3; i < dp.size(); i++) {
            dp[i] = dp[i-2] + dp[i-1];
        }

        return dp[n];
    }
};

//* 空间复杂度优化版本
class Solution2 {
    public:
        int climbStairs(int n) {
            if (n <= 2) return n;   //* 注意特殊情况处理
            int dp[3];
            dp[1] = 1;
            dp[2] = 2;
            for (int i = 3; i <= n; i++) {
                int sum = dp[1] + dp[2];
                dp[1] = dp[2];
                dp[2] = sum;
            }
            return dp[2];
        }
    };
// @lc code=end

