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
        vector<vector<int>> result(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++) {
            result[i][1] = 1;
        }
        for (int j = 1; j <= n ; j++) {
            result[1][j] = 1;
        }

        for (int i = 2; i <= m ; i++) {
            for (int j = 2; j <= n; j++) {
                result[i][j] = result[i-1][j] + result[i][j-1];
            }
        }

        return result[m][n];
    }
};

//* 滚动数组版本
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n);
        
        for (int i = 0; i < n; i++) dp[i] = 1;

        for (int j = 1; j < m; j++) {
            for (int i = 1; i < n; i++) {
                dp[i] += dp[i - 1];
            }
        }
        return dp[n - 1];
    }
};
// @lc code=end

