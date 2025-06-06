/*
 * @lc app=leetcode.cn id=704 lang=cpp
 * 二分查找
 * [704] 二分查找
 */

/*
 * 使用二分前提：数组有序，无重复元素
 * 要注意用middle = (left + right) / 2;可能导致溢出
 * 可以换为middle = left + (right - left) / 2
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int middle = 0;
        while(left <= right)
        //* 左闭右闭
        {
            middle = (left + right) / 2;
            if(nums[middle] > target)
            {
                right = middle - 1;
            }
            else if(nums[middle] < target)
            {
                left = middle + 1;
            }
            else
            {
                return middle;
            }
        }
        return -1;
    }
};
// @lc code=end

