/*
 * @lc app=leetcode.cn id=367 lang=cpp
 * 二分查找
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 0 || num == 1)
        //* num=0或1时，直接返回true
        {
            return true;
        }

        int left = 0;
        int right = num;
        int middle = 0;
        while (left <= right)
        //* 左闭右闭
        {
            middle = left + (right - left) / 2;

            //* middle不为0
            if (middle > num / middle)
            {
                right = middle - 1;
            }
            else if (middle < num / middle)
            {
                left = middle + 1;
            }
            else if (middle * middle == num)
            //! 不满足上面两个的也不一定满足这个，比如num = 17，middle = 4
            {
                return true;
            }
            else break;
        }
        return false;
    }
};
// @lc code=end

