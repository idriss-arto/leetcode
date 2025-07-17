/*
 * @lc app=leetcode.cn id=74 lang=cpp
 * 二分查找
 * [74] 搜索二维矩阵
 */

/*
 * 思路：
 * 因为每行中的整数从左到右按非严格递增顺序排列，
 * 且每行的第一个整数大于前一行的最后一个整数。
 * 所以用两次二分查找就可以。
 * 对矩阵的第一列的元素二分查找，找到最后一个不大于目标值的元素，
 * 然后在该元素所在行中二分查找目标值是否存在。
*/

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int low = 0, high = m - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (matrix[mid][n-1] > target) {
                high = mid - 1;
            }
            else if (matrix[mid][n-1] < target) {
                low = mid + 1;
            }
            else {
                return true;
            }
        }

        if (low == m) return false;
        
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[low][mid] > target) {
                right = mid - 1;
            }
            else if (matrix[low][mid] < target) {
                left = mid + 1;
            }
            else {
                return true;
            }
        }

        return false;
    }
};
// @lc code=end

