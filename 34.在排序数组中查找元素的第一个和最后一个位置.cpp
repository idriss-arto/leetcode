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
        if (leftBorder == -2 || rightBorder == -2) return {-1, -1};
        // 情况三 target 在数组范围中，且数组中存在target
        if (rightBorder - leftBorder > 1) return {leftBorder + 1, rightBorder - 1};
        // 情况二 在数组范围中，且数组中不存在target
        return {-1, -1};
    }

private:
    int searchLeftBorder(vector<int>& nums, int target) {
        //左闭右闭
        int left = 0;
        int right = nums.size() - 1;
        int middle;
        int leftBorder = -2;
        while(left <= right)
        {
            middle = (left + right) / 2;
            if(nums[middle] < target)left = middle + 1;
            else {
                right = middle - 1;
                leftBorder = right;
            }
        }
        return leftBorder;
    }
    
    int searchRightBorder(vector<int>& nums, int target) {
        //左闭右闭
        int left = 0;
        int right = nums.size() - 1;
        int middle;
        int rightBorder = -2;
        while(left <= right)
        {
            middle = (left + right) / 2;
            if(nums[middle] > target)right = middle - 1;
            else {
                left = middle + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
};
// @lc code=end

