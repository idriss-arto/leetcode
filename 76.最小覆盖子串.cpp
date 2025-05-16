/*
 * @lc app=leetcode.cn id=76 lang=cpp
 * 滑动窗口
 ! [76] 最小覆盖子串
 */

// @lc code=start
#include<string>
#include <unordered_map>
using namespace std;

/*
 * 思路：
 * 用unordered_map记录两个字符串中出现字符数量
 * right先往右走，直到满足s从left到right的字符能覆盖t，
 * 再尝试left往右走，缩减s子串长度
*/
class Solution {
public:
    //* 多个函数要用的参数最好不在函数内定义，否则传参很花时间
    unordered_map<char, int> cnt1, cnt2;
    
    bool isOK() {
        for (auto it = cnt2.begin(); it != cnt2.end(); it++) {
            if(cnt1[it->first] < it->second) {
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

        for (int i = 0; i < t.length(); i++) {
            ++cnt2[t[i]];
        }

        int left = 0;
        for (int right = 0; right < s.length(); ++right) {
            ++cnt1[s[right]];
            while (isOK() && left <= right) {
                int subL = right - left + 1;
                if (result > subL) {
                    result = subL;
                    border[0] = left;
                    border[1] = right;
                }
                auto it = cnt1.find(s[left]);
                --it->second;
                //* 或者 cnt1[s[left]]--;
                ++left;
            }
        }

        if (result != INT_MAX) {
            return s.substr(border[0], result);
        }
        else {
            return "";
        }
    }
};

/*
 * 思路：
 * 添加和删除不是看子串是否覆盖t，而是看指针所指向字母的个数是否大于所需
 * 添加时，right指向的字符小于所需才count++，count==t.size()时说明覆盖了
 * 删除时，left指向的字符大于所需才能删除
 * 同时，不再是覆盖了才能删除，而是添加完就能删除
 * 例如t="ABCD"，s="AXXXXBCAXD"，在s遇到第二个A时，就可以把left挪到B
*/
class Solution {
public:
    string minWindow(string s, string t) {
        int hs[123], ht[123];
        int count = 0;
        string res;
        for (auto c : t) ht[c] ++;

        for (int right = 0, left = 0; right < s.size(); right++){
            hs[s[right]]++;
            if (hs[s[right]] <= ht[s[right]]) count++;
            //* 不是看子串是否覆盖t，而是看left所指向字母的个数是否大于所需
            while (hs[s[left]] > ht[s[left]]) {
                hs[s[left]]--;
                left++;
            }
            if (count == t.size()) {
                if (res.empty() || right - left + 1 < res.size()) {
                    res = s.substr(left, right - left + 1);
                }
            }
        }
        return res;

    }
};
// @lc code=end

