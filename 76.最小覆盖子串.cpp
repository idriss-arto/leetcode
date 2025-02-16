/*
 * @lc app=leetcode.cn id=76 lang=cpp
 * 滑动窗口
 * [76] 最小覆盖子串
 */

// @lc code=start
#include<string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    // 多个函数要用的参数最好不在函数内定义，否则传参很花时间
    unordered_map<char, int> cnt1, cnt2;
    
    bool isOK()
    {
        auto it = cnt2.begin();
        while(it != cnt2.end())
        {
            if(cnt1[it->first] < it->second)
            {
                return false;
            }
            it++;
        }
        return true;
        /*
        for (const auto &p: cnt2) {
            if (cnt1[p.first] < p.second) {
                return false;
            }
        }
        return true;
        */
    }

    string minWindow(string s, string t) {
        int result = INT_MAX;
        int border[2] = {0};

        for(int i = 0; i < t.length(); i++)
        {
            ++cnt2[t[i]];
        }

        int left = 0;
        for (int right = 0; right < s.length(); ++right) 
        {
            ++cnt1[s[right]];
            while (isOK() && left <= right)
            {
                int subL = right - left + 1;
                if(result > subL)
                {
                    result = subL;
                    border[0] = left;
                    border[1] = right;
                }
                auto it = cnt1.find(s[left]);
                --it->second;
                ++left;
            }
        }

        if(result != INT_MAX)
        {
            return s.substr(border[0], result);
        }
        else
        {
            return "";
        }
    }

    /*
    string minWindow(string s, string t) {

        int hs[123],ht[123];
        int count = 0;
        string res;
        for(auto c:t) ht[c] ++;

        for(int i = 0, j = 0; i < s.size(); i ++){
            hs[s[i]] ++;
            if(hs[s[i]] <= ht[s[i]]) count ++;
            不是看子串是否覆盖t，而是看left所指向字母的个数是否大于所需
            while(hs[s[j]] > ht[s[j]]) {
                hs[s[j]]--;
                j++;
            }
            if(count == t.size()){
                if(res.empty() || i - j + 1 < res.size()){
                    res = s.substr(j,i - j + 1);
                }
            }
        }
        return res;

    }
    */

};
// @lc code=end

