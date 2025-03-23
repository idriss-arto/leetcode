/*
 * @lc app=leetcode.cn id=69 lang=cpp
 * 二分查找
 * [69] x 的平方根 
 */

/*
 * 有乘法的时候注意一下会不会溢出
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int mySqrt(int x) {
        //* x=0或1时，直接返回x
        if (x == 0 || x == 1)
        {
            return x;
        }

        int left = 0;
        int right = x;
        int middle = 0;
        while(left <= right)
        //* 左闭右闭
        {
            //* 防止left + right越界
            middle = left + (right - left) / 2;

            //* middle不为0
            //* 使用middle > x / middle而不是middle * middle > x
            //* 是为了避免middle * middle越界
            if (middle > x / middle)
            {
                right = middle - 1;
            }
            else if (middle < x / middle)
            {
                left = middle + 1;
            }
            else 
            {
                return middle;
            }
        }
        return right;
    }
};
// @lc code=end

