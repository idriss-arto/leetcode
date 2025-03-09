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
        //* slow不能为0，不然第一个数会被错过
        //* 与前一个值比较，即fast与fast-1进行比较，是去重
        //* 与后一个值比较，即fast和fast+1比较的话，是判断fast指向的值是否只出现一次，但最后一个数没得比
        int slow = 1, fast = 1;
        for(; fast < nums.size(); fast++)
        {
            if(nums[fast] != nums[fast - 1])
            {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
// @lc code=end

