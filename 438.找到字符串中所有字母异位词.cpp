/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * 滑动窗口，哈希
 ! [438] 找到字符串中所有字母异位词
 */

/*
 * 思路:
 * 滑动窗口加哈希(因为确定只用小写字母作为key，所以直接用数组模拟hash即可，不用unordered_map)
 * 滑动窗口移动时，左边出界的字母对应计数减一，右边新入界的字母对应计数加一
 ! 注意，两个vector可以直接用"=="来判断是否相等
*/

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            //* 如果SCount和pCount用的是unordered_map，需要加下面一行代码
            //* if (sCount[s[i]] == 0) sCount.erase(s[i]);
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                //! 此时s中子串开头位置为i + 1
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};

int main() {
    string s = "cbaebabacd", p = "abc";
    Solution a;
    vector<int> res(a.findAnagrams(s, p));
    return 0;
}
// @lc code=end

