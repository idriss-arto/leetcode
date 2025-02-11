/*
 * @lc app=leetcode.cn id=278 lang=cpp
 * 二分查找
 * [278] 第一个错误的版本
 */

// @lc code=start
// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n, middle = 0;
        while(left < right)
        {
            middle = left + (right - left) / 2;
            if(isBadVersion(middle))
            {
                //因为middle也可能是第一个错误的版本，所以不能是right = middle - 1;
                //此时如果while循环判断是left <= right，则陷入死循环（left = right = middle）
                right = middle;
            }
            else
            {
                left = middle + 1;
            }
        }
        return left;
    }
};
// @lc code=end

