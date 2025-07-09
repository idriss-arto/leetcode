/*
 * @lc app=leetcode.cn id=240 lang=cpp
 * 矩阵
 ! [240] 搜索二维矩阵 II
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 官方题解，Z 字形查找
 * 思路：
 * 从矩阵 matrix 的右上角 (0,n−1) 进行搜索。
 * 
 * 在每一步的搜索过程中，如果我们位于位置 (x,y)，
 * 那么我们希望在以 matrix 的左下角为左下角、以 (x,y) 为右上角的矩阵中进行搜索，
 * 即行的范围为 [x,m−1]，列的范围为 [0,y]
 * 
 * 可能的情况有三种：
 * 1.
 * 如果 matrix[x,y]==target，说明搜索完成
 * 
 * 2.
 * 如果 matrix[x,y]>target，由于每一列的元素都是升序排列的，
 * 那么在当前的搜索矩阵中，所有位于第 y 列的元素都是严格大于 target 的，
 * 因此我们可以将它们全部忽略，即让 y 减少 1
 * 
 * 3.
 * 如果 matrix[x,y]<target，由于每一行的元素都是升序排列的，
 * 那么在当前的搜索矩阵中，所有位于第 x 行的元素都是严格小于 target 的，
 * 因此我们可以将它们全部忽略，即让 x 增加 1。
 * 
 * 时间复杂度O（m+n）
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0) {
            if (matrix[x][y] == target) return true;
            else if (matrix[x][y] < target) x++;
            else y--;
        }
        return false;
    }
};

/*
 * 官方题解二，二分
 * 使用lower_bound函数，不用自己写二分
 * 时间复杂度为O（m*log(n)）
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (const auto& row: matrix) {
            auto it = lower_bound(row.begin(), row.end(), target);
            if (it != row.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};

//* 我的解法，本质是对每一行做二分查找
//* 时间复杂度O（m*log(n)）
class Solution {
public:
    bool searchBinary(vector<int>& nums, const int& target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        
        for (int i = 0; i < m; i++) {
            //* 当前行最大值都比target小
            if (matrix[i][n-1] < target) continue;

            //* 当前行最小值都比target大，加上之前的行也没找到，可以直接返回false
            if (matrix[i][0] > target) return false;

            //* 剩下的情况才在当前行找
            if (searchBinary(matrix[i], target)) {
                return true;
            }
        }

        return false;
    }
};
// @lc code=end

