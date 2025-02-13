/*
 * @lc app=leetcode.cn id=633 lang=cpp
 * 双指针
 * [633] 平方数之和
 */

// @lc code=start
#include<math.h>
using namespace std;
class Solution {
public:
    bool judgeSquareSum(int c) {
        int left = 0, right = sqrt(c);
        while(left <= right)
        {
            if(pow(left, 2) + pow(right, 2) == c)
            {
                return true;
            }
            else if(pow(left, 2) + pow(right, 2) > c)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return false;
    }
};
// @lc code=end

