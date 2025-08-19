/*
 * @lc app=leetcode.cn id=540 lang=cpp
 * 二分查找
 * [540] 有序数组中的单一元素
 */

/*
 * 思路：设m为一偶数，n为只出现一次那个数的位置（显然n为偶数）
 * 当m < n时，nums[m] = nums[m + 1]
 * 当m >= n时，nums[m] != nums[m + 1]
*/

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        
        int left = 0, right = nums.size() - 1, middle = 0;
        while(left <= right)
        {
            middle = left + (right - left) / 2;
            if(middle % 2 == 1)
            //* 保证middle为偶数
            {
                middle--;
            }
            if(nums[middle] == nums[middle + 1])
            //* 此时所求位置为大于middle的偶数
            {
                left = middle + 2;
            }
            else
            //* 此时所求位置为小于等于middle的偶数
            {
                right = middle - 2;
            }
        }
        return nums[middle];
    }
};
// @lc code=end

