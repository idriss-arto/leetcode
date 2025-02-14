/*
 * @lc app=leetcode.cn id=209 lang=cpp
 * 滑动窗口
 * [209] 长度最小的子数组
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int begin = 0, end = 0, sum = 0, result = nums.size() + 1;
        for(; end < nums.size(); end++)
        {
            sum += nums[end];
            while(sum >= target)
            {
                int subL = end - begin + 1;
                result = (result > subL ? subL : result);
                sum -= nums[begin++];
            }
        }
        if(result == nums.size() + 1)
        {
            result = 0;
        }
        return result;
    }
};
// @lc code=end

