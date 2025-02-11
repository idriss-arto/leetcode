/*
 * @lc app=leetcode.cn id=540 lang=cpp
 * 二分查找
 * [540] 有序数组中的单一元素
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1, middle = 0;
        while(left < right)
        {
            middle = left + (right - left) / 2;
            if(middle % 2 == 1)
            {
                middle--;
            }
            if(nums[middle] == nums[middle + 1])
            {
                left += 2;
            }
            else
            {
                right = middle;
            }
        }
        return nums[middle];
    }
};
// @lc code=end

