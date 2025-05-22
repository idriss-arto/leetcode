/*
 * @lc app=leetcode.cn id=48 lang=cpp
 * 矩阵操作
 * [48] 旋转图像
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 官方题解，原地旋转
 ! matrix[i][j] 旋转后应放在 matrix[j][n - 1 - i]，即matrix[j][n - 1 - i] = matrix[i][j]
 * 同理可得：
 * matrix[i][j] = matrix[n - i - j][i]
 * matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
 * matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};

/*
 * 官方题解，翻转
 * 一次上下翻转，一次主对角线翻转。结果等于顺时针旋转90度
 * 例如：
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6 =>  4 5 6 =>  8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        //* 水平翻转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix[i][j], matrix[n - i - 1][j]);
            }
        }
        //* 主对角线翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};

/*
 * 我的题解
 * 本质思路还是旋转，但写的麻烦
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        int offset = 0;

        while (n - 2*offset >= 2) {
            int cnt = n - 2 * offset;
            for (int i = 0; i < cnt - 1; i++) {
                int nowi = offset;
                int nowj = offset + i;
                int nexti = nowj;
                int nextj = n - 1 - nowi;
                int now = matrix[nowi][nowj];
                int tmp;

                for (int j = 1; j <= 4; j++) {
                    tmp = matrix[nexti][nextj];
                    matrix[nexti][nextj] = now;
                    now = tmp;
                    nowi = nexti;
                    nowj = nextj;
                    nexti = nowj;
                    nextj = n - 1 - nowi;
                }
            } 
            offset++;
        }
    }
};
// @lc code=end

