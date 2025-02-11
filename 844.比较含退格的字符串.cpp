/*
 * @lc app=leetcode.cn id=844 lang=cpp
 * 快慢指针
 * [844] 比较含退格的字符串
 */

// @lc code=start
#include <string>
using namespace std;
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int sSlow = 0, sFast = 0;
        for(; sFast < s.length(); sFast++)
        {
            
            if(s[sFast] != '#')
            {
                s[sSlow++] = s[sFast];
            }
            else if(s[sFast] == '#' && sSlow != 0)
            {
                sSlow -= 1;
            }
            else continue;
        }

        int tSlow = 0, tFast = 0;
        for(; tFast < t.length(); tFast++)
        {
            if(t[tFast] != '#')
            {
                t[tSlow++] = t[tFast];
            }
            else if(t[tFast] == '#' && tSlow != 0)
            {
                tSlow -= 1;
            }
            else continue;
        }

        if(sSlow != tSlow)return false;

        for(int i = 0; i < sSlow; i++)
        {
            if(s[i] != t[i])return false;
        }


        return true;
    }
};
// @lc code=end

