/*
 * @lc app=leetcode.cn id=74 lang=cpp
 * 二分查找
 * [74] 搜索二维矩阵
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

