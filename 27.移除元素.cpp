/*
 * @lc app=leetcode.cn id=27 lang=cpp
 * 快慢指针
 * [27] 移除元素
 */

// @lc code=star
#include <vector>
using namespace std;
class Solution {
public:
    //* slow是坑，fast找萝卜
    int removeElement(vector<int>& nums, int val) {
        int slow = 0, fast = 0;
        for(; fast < nums.size(); fast++)
        {
            if(nums[fast] != val)
            {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
// @lc code=end

