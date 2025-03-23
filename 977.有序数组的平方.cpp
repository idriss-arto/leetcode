/*
 * @lc app=leetcode.cn id=977 lang=cpp
 * 双指针
 * [977] 有序数组的平方
 */

/*
 * 思路：
 * 在包含负数的数组里，平方后最大的数是原来绝对值最大的数
 * 所以从数组两端开始找，从后往前填result数组
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> result(nums.size(), 0);
        int i = 0, j = nums.size() - 1, k = nums.size() - 1;
        while (i <= j)
        {
            if ((nums[i] * nums[i]) > (nums[j] * nums[j]))
            //* 可能越界，最好用abs(nums[i]) > abs(nums[j])
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

