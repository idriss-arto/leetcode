/*
 * @lc app=leetcode.cn id=977 lang=cpp
 * 双指针
 * [977] 有序数组的平方
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> result(nums.size(), 0);
        int i = 0, j = nums.size() - 1, k = nums.size() - 1;
        while(i <= j)
        {
            if((nums[i] * nums[i]) > (nums[j] * nums[j]))
            // 可能越界，最好用abs(nums[i]) > abs(nums[j])
            {
                result[k] = nums[i] * nums[i];
                k--;
                i++;
            }
            else
            {
                result[k] = nums[j] * nums[j];
                k--;
                j--;
            }
        }
        return result;
    }
};
// @lc code=end

