/*
 * @lc app=leetcode.cn id=240 lang=cpp
 * 矩阵
 ! [240] 搜索二维矩阵 II
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 官方题解思路：
 * Z 字形查找，从矩阵 matrix 的右上角 (0,n−1) 开始进行搜索。
 * 假设当前遍历到位置（x，y），显然我们只需考虑以矩阵左下角作为左下角和（x，y）作为右上角的小矩阵。
 * 1.
 * 如果 matrix[x,y]=target，说明搜索完成；
 * 2.
 * 如果 matrix[x,y]>target，由于每一列的元素都是升序排列的，
 * 那么在当前的搜索矩阵中，所有位于第 y 列的元素都是严格大于 target 的，
 * 因此我们可以将它们全部忽略，即可以将 y 减少 1；
 * 3.
 * 如果 matrix[x,y]<target，由于每一行的元素都是升序排列的，
 * 那么在当前的搜索矩阵中，所有位于第 x 行的元素都是严格小于 target 的，
 * 因此我们可以将它们全部忽略，即可以将 x 增加 1。
 * 4.
 * 在搜索的过程中，如果我们超出了矩阵的边界，那么说明矩阵中不存在 target。
 * 
 * 时间复杂度O(m+n)
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0) {
            if (matrix[x][y] == target) {
                return true;
            }
            if (matrix[x][y] > target) {
                --y;
            }
            else {
                ++x;
            }
        }
        return false;
    }
};

/*
 * 我的解法，思路：
 * 对每一行二分查找，找到了返回true，
 * 没找到分情况，
 * 1.right == -1，说明当前行最小值大于target，因为上面已经遍历过，所以直接返回false
 * 2.left == n，说明当前行最大值小于target，在下一行[0, n-1]继续遍历
 * 3.剩余情况，left为比target大的最小值，right为比target小的最大值，在下一行[0, right]继续遍历
 *
 * 时间复杂度O(m*n*log(n))
 */
class Solution {
public:
    bool searchBinary(vector<int>& nums, int& left, int& right, const int& target) {
        if (left > right) return false;
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

        int left = 0, right = n - 1;
        for (int i = 0; i < m; i++) {
            //* 当前行找到
            if (searchBinary(matrix[i], left, right, target)) {
                return true;
            }
            //* 当前行没找到，处理下一行二分查找左右边界
            else {
                //* 当前行最小值都比target大
                if (right == -1) return false;
                
                //* 当前行最大值都比target小
                if (left == n) {
                    left = 0;
                    right = n - 1;
                    continue;
                }

                //* 当前行找到比target大的最小值（left），和比target小的最大值（right）
                //* 下一行在[0, right]继续遍历
                left = 0;
            }
        }

        return false;
    }
};

/*
 * 别人的解法，思路：
 * 大致思路还是二分查找，但做了很多剪枝
 * 
*/
class Solution {
public:
    bool searchBinary(vector<int>& nums, int& left, int& right, const int& target) {
        if (left > right) return false;
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

        int left = 0, right = n - 1;
        for (int i = 0; i < m; i++) {
            //* 当前行最小值大于target，由于上面已经遍历了，直接返回false
            if (matrix[i][0] > target) return false;

            //* 当前行最大值小于target，跳过当前行
            if (matrix[i][n-1] < target) continue;

            //* 当前行找到
            if (searchBinary(matrix[i], left, right, target)) {
                return true;
            }
            //* 当前行没找到，处理下一行二分查找左右边界
            else {
                left = 0;
            }
        }

        return false;
    }
};
// @lc code=end

