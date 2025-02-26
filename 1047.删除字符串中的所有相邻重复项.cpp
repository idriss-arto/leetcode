/*
 * @lc app=leetcode.cn id=1047 lang=cpp
 * 栈
 * [1047] 删除字符串中的所有相邻重复项
 */

// @lc code=start
#include <stack>
#include <algorithm>
#include <string>
using namespace std;
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> sta;
        for (char c : s) {
            if (!sta.empty() && sta.top() == c) {
                sta.pop();
                continue;
            }
            sta.push(c);
        }
        string result = "";
        while (!sta.empty()) { // 将栈中元素放到result字符串汇总
            result += sta.top();
            sta.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string removeDuplicatesV2(string S) {
        string result;
        for(char s : S) {
            if(result.empty() || result.back() != s) {
                result.push_back(s);
            }
            else {
                result.pop_back();
            }
        }
        return result;
    }
};
// @lc code=end

