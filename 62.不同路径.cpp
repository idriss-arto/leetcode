/*
 * @lc app=leetcode.cn id=62 lang=cpp
 * 动态规划
 * [62] 不同路径
 */

// @lc code=start
#include <vector>
using namespace std;

//* 普通版本
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        //* 初始化第一行和第一列
        for (int i = 1; i <= m; i++) {
            dp[i][1] = 1;
        }
        for (int j = 1; j <= n; j++) {
            dp[1][j] = 1;
        }

        for (int i = 2; i <= m; i++) {
            for (int j = 2; j <= n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m][n];
    }
};

//* 滚动数组版本
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n);
        
        for (int i = 0; i < n; i++) dp[i] = 1;

        for (int i = 1; i < m; i++) {
            //* 注意这里是正常从前往后遍历
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};
// @lc code=end

