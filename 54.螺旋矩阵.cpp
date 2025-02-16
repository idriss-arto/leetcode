/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * 循环边界
 * [54] 螺旋矩阵
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
 private:
    static constexpr int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};


public:
    // 官方题解，思路更简单
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(columns));
        int total = rows * columns;
        vector<int> order(total);

        int row = 0, column = 0;
        int directionIndex = 0;
        for (int i = 0; i < total; i++) {
            order[i] = matrix[row][column];
            visited[row][column] = true;
            // 下一个位置超界或已被访问
            int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
            if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
                directionIndex = (directionIndex + 1) % 4;
            }
            row += directions[directionIndex][0];
            column += directions[directionIndex][1];
        }
        return order;
    }

    vector<int> mySpiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int loop = 0;
        int count = 0;
        int offset = 0;
        
        vector<int> res(m * n, 0);
        int i, j;
        while(loop++ < min(m, n) / 2) {
            i = offset;
            j = offset;
            for (; j < n - 1 - offset; j++) {
                res[count++] = matrix[i][j];
            }
            for (; i < m - 1 - offset; i++) {
                res[count++] = matrix[i][j];
            }
            for (; j > offset; j--) {
                res[count++] = matrix[i][j];
            }
            for (; i > offset; i--) {
                res[count++] = matrix[i][j];
            }
            offset++;
        }
        if (m < n && (m % 2 == 1)) {
            i = offset;
            j = offset;
            for (; j <= n - 1 - offset; j++) {
                res[count++] = matrix[i][j];
            }
        }
        else if (m >= n && (n % 2 == 1)){
            i = offset;
            j = offset;
            for (; i <= m - 1 - offset; i++) {
                res[count++] = matrix[i][j];
            }
        }

        return res;
    }
};
// @lc code=end

