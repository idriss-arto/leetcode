/*
 * @lc app=leetcode.cn id=33 lang=cpp
 * 二分查找
 ! [33] 搜索旋转排序数组
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 我的题解
 * 思路：
 * 当前区间[left, right]，
 * 如果左边界大于右边界，则将当前区间从中间划分为2个子区间，递归处理。
 * 如果左边界小于右边界，则二分查找。
*/ 
class Solution {
public:
    int searchBinary(vector<int>& nums, int left, int right, const int& target) {
        if (left > right) return -1;

        int mid = left + (right - left) / 2;

        //* 左边界小于右边界，说明当前区间无序，划分为2个子区间处理
        if (nums[left] > nums[right]) {
            int left_result = searchBinary(nums, left, mid, target);
            int right_result = searchBinary(nums, mid+1, right, target);
            if (left_result != -1) {
                return left_result;
            } 
            if (right_result != -1)  {
                return right_result;
            }
            return -1;
        }

        //* target超出当前区间范围
        if (nums[left] > target || nums[right] < target) {
            return -1;
        }

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] > target) right = mid - 1;
            else left = mid + 1;
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        return searchBinary(nums, 0, nums.size()-1, target);
    }
};

/*
 * 官方题解
 * 思路：
 * 当前 mid 为分割位置分割出来的两个部分 [l, mid] 和 [mid + 1, r] 时，一定有一部分的数组是有序的。
 * 可根据有序的那个部分确定该如何改变二分查找的上下界，因为能够根据有序的那部分判断出 target 在不在这个部分：
 * 如果 [l, mid - 1] 是有序数组，且 target 的大小满足 [nums[l],nums[mid])，则应该将搜索范围缩小至 [l, mid - 1]，否则在 [mid + 1, r] 中寻找。
 * 如果 [mid, r] 是有序数组，且 target 的大小满足 (nums[mid+1],nums[r]]，则应该将搜索范围缩小至 [mid + 1, r]，否则在 [l, mid - 1] 中寻找。
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            //* 如果找到目标，直接返回
            if (nums[mid] == target) {
                return true;
            }
            
            //* 左半部分有序
            else if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            } 
            //* 右半部分有序
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        
        return false;
    }
};
// @lc code=end

