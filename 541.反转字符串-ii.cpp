/*
 * @lc app=leetcode.cn id=541 lang=cpp
 * 字符串
 * [541] 反转字符串 II
 */

/*
 * 灵活运用库函数
 * reverse(开始位置的迭代器, 结束位置的迭代器)，
 * 如reverse(s.begin() + i, s.end())
*/

// @lc code=
#include<vector>
#include<string>
#include<math.h>
#include<algorithm>
using namespace std;
class Solution {
public:
    /* 
     * 我的解法
     * 双指针先反转前k个（如果有的话）
     * 再将left和right加2k，根据与字符串边界对比结果进行相应处理
    */
    string myReverseStr(string s, int k) {
        int left = 0, right = min(k, (int)s.size()) - 1;
        while (1) {
            for(int i = left, j = right; i <= j; i++, j--) {
                swap(s[i], s[j]);
            }
            left += 2 * k;
            right += 2 * k;
            if (left >= s.size()) {
                break;
            }
            else if(right >= s.size()) {
                right = s.size() - 1;
                for(; left <= right; left++, right--) {
                    swap(s[left], s[right]);
                }
                break;
            }
            else {
                continue;
            }
        }
        return s;
    }

    //* 题解解法，思路是一样的，因为用了reverse库函数显得简洁
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            //* 1. 每隔 2k 个字符的前 k 个字符进行反转
            //* 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
            if (i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k );
            } else {
                //* 3. 剩余字符少于 k 个，则将剩余字符全部反转。
                reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
};
// @lc code=end

