/*
 * @lc app=leetcode.cn id=367 lang=cpp
 * 二分查找
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution {
public:
    bool isPerfectSquare(int num) {
        //左闭右闭
        int left = 0;
        int right = num;
        int middle = 0;
        while(left <= right)
        {
            middle = left + (right - left) / 2;
            //num=0或1时，middle为0
            if(middle == 0)return num == 1 ? 1 : 0;
            //middle不为0
            if(middle > num / middle)right = middle - 1;
            else if(middle < num / middle)left = middle + 1;
            else if(middle * middle == num)return true;
            else break;
        }
        return false;
    }
};
// @lc code=end

