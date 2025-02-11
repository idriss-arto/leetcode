/*
 * @lc app=leetcode.cn id=153 lang=cpp
 * 二分查找
 * [153] 寻找旋转排序数组中的最小值
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        //最小值为x的话，旋转后x左边的值大于nums[right]，x右边的值小于nums[right]
        int left = 0, right = nums.size() - 1, middle = 0;
        while(left < right)
        {
            middle = left + (right - left) / 2;
            if(nums[middle] > nums[right])
            //此时x在[middle + 1, right]
            {
                left = middle + 1;
            }
            else 
            //nums[middle] <= nums[right]，此时x在[left, middle]
            {
                right = middle;
            }
        }
        return left;
    }
};
// @lc code=end

