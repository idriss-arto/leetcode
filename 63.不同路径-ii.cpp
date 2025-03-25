/*
 * @lc app=leetcode.cn id=63 lang=cpp
 * 动态规划
 * [63] 不同路径 II
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> result(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] != 1) result[i][0] = 1;
            //* 遇到有障碍后，第一列后面没有路径能到达
            else break;
        }
        for (int j = 0; j < n ; j++) {
            if (obstacleGrid[0][j] != 1) result[0][j] = 1;
            //* 同理
            else break;
        }

        for (int i = 1; i < m ; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) result[i][j] = 0;
                else result[i][j] = result[i-1][j] + result[i][j-1];
            }
        }

        return result[m-1][n-1];
    }
};
// @lc code=end

