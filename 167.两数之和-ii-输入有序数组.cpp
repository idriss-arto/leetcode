/*
 * @lc app=leetcode.cn id=167 lang=cpp
 * 双指针
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while(left < right)
        {
            if(numbers[left] + numbers[right] == target)
            {
                return vector<int>{left + 1, right + 1};
            }
            else if(numbers[left] + numbers[right] > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return vector<int>{-1, -1};
    }
};
// @lc code=end

