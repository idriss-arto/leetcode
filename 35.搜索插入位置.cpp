/*
 * @lc app=leetcode.cn id=35 lang=cpp
 * 二分查找
 * [35] 搜索插入位置
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        //左闭右闭
        int left = 0;
        int right = nums.size() - 1;
        int middle = 0;
        while(left <= right)
        {
            middle = left + ((right - left) / 2);
            if(nums[middle] > target)right = middle - 1;
            else if(nums[middle] < target)left = middle + 1;
            else return middle;
        }
        // 分别处理如下四种情况
        // 目标值在数组所有元素之前  [0, -1]
        // 目标值等于数组中某一个元素  return middle;
        // 目标值插入数组中的位置 [right, left]，return  right + 1
            //在while循环最后一次循环里，left=right=middle
            //此时在对比大小后，right一定指向数组中刚好小于target那一个下标
        // 目标值在数组所有元素之后的情况 [left, right]， 因为是右闭区间，所以 return right + 1
        return right + 1;
        //return left;   也可以
    }
};
// @lc code=end

