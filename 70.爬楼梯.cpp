/*
 * @lc app=leetcode.cn id=70 lang=cpp
 * 动态规划
 * [70] 爬楼梯
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> result(n+1);
        result[0] = 0;
        result[1] = 1;
        result[2] = 2;
        for (int i = 3; i < result.size(); i++) {
            result[i] = result[i-2] + result[i-1];
        }
        return result[n];
    }
};

//* 优化空间复杂度版本
class Solution2 {
    public:
        int climbStairs(int n) {
            if (n <= 1) return n;
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

