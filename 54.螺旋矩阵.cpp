/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * 模拟，循环边界
 * [54] 螺旋矩阵
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
 private:
    static constexpr int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};


public:
    //* 官方题解，思路更简单
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(columns));
        int total = rows * columns;     //* 记录一共有多少个数
        vector<int> order(total);

        int row = 0, column = 0;
        int directionIndex = 0;
        for (int i = 0; i < total; i++) {
            order[i] = matrix[row][column];
            visited[row][column] = true;
            //* 根据directions数组获取循环方向，求得下一个位置
            int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
            //* 下一个位置超界或已被访问
            if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
                //* 利用directions数组改变循环方向
                directionIndex = (directionIndex + 1) % 4;
            }
            row += directions[directionIndex][0];
            column += directions[directionIndex][1];
        }
        return order;
    }

    vector<int> mySpiralOrder(vector<vector<int>>& matrix) {
        //* 先获取矩阵大小
        int m = matrix.size();
        int n = matrix[0].size();
        int loop = 0;
        int count = 0;          //* 计数已经读了多少个值
        int offset = 0;
        
        vector<int> res(m * n, 0);
        int i, j;
        //* 会进行{min(m, n) / 2}次圈
        while(loop++ < min(m, n) / 2) {
            //* 定义当前圈开始的位置
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
        //* 当行小于列，并且行数为奇数时，最中间一行的中间一些列没被读到
        if (m < n && (m % 2 == 1)) {
            i = offset;
            j = offset;
            for (; j <= n - 1 - offset; j++) {
                res[count++] = matrix[i][j];
            }
        }
        //* 当列小于行，并且列数为奇数时，最中间一列的中间一些行没被读到
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

