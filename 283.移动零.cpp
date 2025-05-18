/*
 * @lc app=leetcode.cn id=283 lang=cpp
 * 双指针
 * [283] 移动零
 */

/*
 * 思路：
 * 使用双指针，左指针指向当前已经处理好的序列之后第一个元素，右指针指向待处理序列的头部。
 * 右指针不断向右移动，每次右指针指向非零数，则将左右指针对应的数交换，同时左指针右移。
 * 显然，遇到0之前，left和right指向同一元素，即自己与自己交换
 * 遇到第一个0之后，left左边是已经处理好的序列，left指向第一个0
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0, fast = 0;
        for (; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);
                slow++;
            }
        }
    }
};
// @lc code=end

