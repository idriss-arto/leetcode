/*
 * @lc app=leetcode.cn id=33 lang=cpp
 * 二分查找
 * [33] 搜索旋转排序数组
 */

// @lc code=start
#include <vector>
using namespace std;

//* 我的题解
class Solution {
public:
    int searchBinary(vector<int>& nums, int left, int right, const int& target) {
        if (left > right) return -1;

        int mid = left + (right - left) / 2;
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

//* 官方题解
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
                } else {
                    left = mid + 1;
                }
            } 
            //* 右半部分有序
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return false;
    }
};
// @lc code=end

