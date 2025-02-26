/*
 * @lc app=leetcode.cn id=20 lang=cpp
 * 栈
 * [20] 有效的括号
 */

// @lc code=start
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> sta;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                sta.push(s[i]);
            }
            else {
                char x;
                if (!sta.empty()) {
                    x = sta.top();
                }
                else {
                    return false;
                }
                if ((s[i] == ')' && x == '(') ||
                    (s[i] == ']' && x == '[') ||
                    (s[i] == '}' && x == '{')) 
                {
                    sta.pop();
                    continue;
                }
                else {
                    return false;
                }
            }
        }
        if (sta.empty()) {
            return true;
        }
        else {
            return false;
        }
    }
};
// @lc code=end

