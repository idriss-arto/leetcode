/*
 * @lc app=leetcode.cn id=34 lang=cpp
 * 二分查找
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = searchLeftBorder(nums, target);
        int rightBorder = searchRightBorder(nums, target);
        // 情况一 在数组范围的右边或者左边
        // if (leftBorder == -1 || rightBorder == nums.size()) return {-1, -1};
        // 情况三 target 在数组范围中，且数组中存在target
        if (rightBorder - leftBorder > 1) return {leftBorder + 1, rightBorder - 1};
        // 情况二 在数组范围中，且数组中不存在target
        return {-1, -1};
    }

private:
    // 找左边界即找比target小的最大值位置
    int searchLeftBorder(vector<int>& nums, int target) {
        // 左闭右闭
        int left = 0;
        int right = nums.size() - 1;
        int middle;
        int leftBorder = 0;
        while(left <= right)
        {
            middle = (left + right) / 2;
            if(nums[middle] < target)
            // middle比target小时，这个middle可能是小于target的最大值
            {
                leftBorder = middle;
                left = middle + 1;
            }
            else
            // middle大于等于target时，小于target的最大值一定在middle左边
            {
                right = middle - 1;
                leftBorder = right;
            }
        }
        return leftBorder;
    }
    
    // 找右边界即找比target大的最小值位置
    int searchRightBorder(vector<int>& nums, int target) {
        
        int left = 0;
        int right = nums.size() - 1;
        int middle;
        int rightBorder = 0;
        while(left <= right)
        // 左闭右闭
        {
            middle = (left + right) / 2;
            if(nums[middle] > target)
            // middle比target大时，这个middle可能是大于target的最小值
            {
                rightBorder = middle;
                right = middle - 1;
            }
            else 
            // middle小于等于target时，大于target的最小值一定在middle右边
            {
                left = middle + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
};
// @lc code=end

