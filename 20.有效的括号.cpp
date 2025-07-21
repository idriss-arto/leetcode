/*
 * @lc app=leetcode.cn id=20 lang=cpp
 * 栈
 * [20] 有效的括号
 */

/*
 * 思路：
 * 栈的经典应用，匹配问题。
 * 根据当前字符是左括号还是右括号选择压栈或者弹栈，
 * 中间匹配失败的话则返回失败，匹配全成功的话，在字符串结束时栈为空说明成功。
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
                if (sta.empty()) {
                    return false;
                }
                char x = sta.top();
                if ((s[i] == ')' && x == '(') ||
                    (s[i] == ']' && x == '[') ||
                    (s[i] == '}' && x == '{')) {
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

