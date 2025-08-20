/*
 * @lc app=leetcode.cn id=680 lang=cpp
 * 双指针
 * [680] 验证回文串 II
 */

/*
 * 思路：
 * 在使用双指针遍历字符串时，如果出现两个指针指向的字符不相等的情况，
 * 我们就试着删除一个字符，再判断删除完之后的字符串是否是回文字符串。
*/

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while(left <= right)
        {
            if(s[left] == s[right])
            {
                left++, right--;
            }
            else
            {
                return isPalindrome(s, left + 1, right) || 
                       isPalindrome(s, left, right - 1);
            }

        }
        return true;
    }

    bool isPalindrome(string s, int left, int right) {
        while(left <= right)
        {
            if(s[left] == s[right])
            {
                left++, right--;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

