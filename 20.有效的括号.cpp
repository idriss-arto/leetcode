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
            //* 左括号压栈
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                sta.push(s[i]);
            }
            //* 右括号，看栈顶的左括号是否匹配
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
        //* 读取完括号串，栈为空说明所有括号匹配完成
        if (sta.empty()) {
            return true;
        }
        else {
            return false;
        }
    }
};
// @lc code=end

