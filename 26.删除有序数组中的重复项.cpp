/*
 * @lc app=leetcode.cn id=26 lang=cpp
 * 快慢指针
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // slow不能为0，不然第一个数会被错过
        int slow = 1, fast = 0;
        for(; fast < nums.size() - 1; fast++)
        {
            if(nums[fast + 1] != nums[fast])
            {
                nums[slow++] = nums[fast + 1];
            }
        }
        return slow;
    }
};
// @lc code=end

