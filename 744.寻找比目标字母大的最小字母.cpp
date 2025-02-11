/*
 * @lc app=leetcode.cn id=744 lang=cpp
 * 二分查找
 * [744] 寻找比目标字母大的最小字母
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0, right = letters.size() - 1, middle = 0;
        while(left <= right)
        {
            middle = left + (right - left) / 2;
            if(letters[middle] <= target)
            {
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
        }
        return left != letters.size() ? letters[left] : letters[0];
    }
};
// @lc code=end

