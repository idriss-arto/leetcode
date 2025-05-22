/*
 * @lc app=leetcode.cn id=73 lang=cpp
 * 矩阵
 * [73] 矩阵置零
 */

/*
 * 思路一：
 * 两个标记数组分别记录每一行和每一列是否有零出现。
 * 具体地，
 * 我们首先遍历该数组一次，
 * 如果某个元素为 0，那么就将该元素所在的行和列所对应标记数组的位置置为 true。
 * 最后我们再次遍历该数组，用标记数组更新原数组即可。
 * 
 * 思路二：
 * 用矩阵的第一行和第一列代替方法一中的两个标记数组，以达到 O(1) 的额外空间。
 * 但这样会导致原数组的第一行和第一列被修改，
 * 无法记录它们是否原本包含 0。因此我们需要额外使用两个标记变量分别记录第一行和第一列是否原本包含 0。
 * 在实际代码中，
 * 我们首先预处理出两个标记变量，
 * 接着使用其他行与列去处理第一行与第一列，
 * 然后反过来使用第一行与第一列去更新其他行与列，
 * 最后使用两个标记变量更新第一行与第一列即可。
*/

// @lc code=start
#include <vector>
using namespace std;

//* 法一，空间复杂度O(m+n)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> row(m), col(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) {
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row[i] || col[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

//* 法二，空间复杂度O(1)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        bool row0_zero = false, col0_zero = false;

        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) row0_zero = true;
        }
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) col0_zero = true;
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int j = 1; j < n; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (row0_zero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        if (col0_zero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }

        return ;
    }
};
// @lc code=end

