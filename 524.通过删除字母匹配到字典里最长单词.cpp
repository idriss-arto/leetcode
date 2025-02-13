/*
 * @lc app=leetcode.cn id=524 lang=cpp
 * 双指针 或者 动态规划（尚未实现）
 * [524] 通过删除字母匹配到字典里最长单词
 */

// @lc code=start
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    bool isSubstr(string s, string p) {
        int i = 0, j = 0;
        while(i < s.length() && j < p.length())
        {
            if(s[i++] == p[j])
            {
                j++;
            }
        }
        return j == p.length();
    }

    string findLongestWord(string s, vector<string>& dictionary) {
        string Longest = "";
        for(string p : dictionary)
        {
            int l1 = Longest.length(), l2 = p.length();
            if(l1 > l2 || (l1 == l2 && Longest.compare(p) < 0))
            {
                continue;
            }
            if(isSubstr(s, p))
            {
                Longest = p;
            }
        }
        return Longest;
    }
};
// @lc code=end

