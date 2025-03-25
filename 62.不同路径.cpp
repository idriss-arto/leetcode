/*
 * @lc app=leetcode.cn id=62 lang=cpp
 * 动态规划
 * [62] 不同路径
 */

// @lc code=start
#include <vector>
using namespace std;
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
// @lc code=end

