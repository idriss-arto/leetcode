/*
 * @lc app=leetcode.cn id=344 lang=cpp
 * 字符串，双指针
 * [344] 反转字符串
 */

/*
 * 思路：双指针，交换两个指针指向的值
*/

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        for (; left <= right; left++, right--) {
            swap(s[left], s[right]);
        }
    }
};
// @lc code=end

