/*
 * @lc app=leetcode.cn id=283 lang=cpp
 * 快慢指针
 * [283] 移动零
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0, fast = 0;
        for (; fast < nums.size(); fast++)
        {
            if (nums[fast] != 0)
            {
                nums[slow] = nums[fast];
                if (slow != fast)
                //* 注意不要错误置零，比如[1]，[2,0]
                {
                    nums[fast] = 0;
                }
                slow++;
            }
        }
    }
};
// @lc code=end

