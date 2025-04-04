/*
 * @lc app=leetcode.cn id=1047 lang=cpp
 * 栈
 * [1047] 删除字符串中的所有相邻重复项
 */

/*
 * 思路：
 * 栈的经典应用，匹配问题
 * 根据当前字符是栈顶元素是否相同确定是弹栈还是压栈
*/

// @lc code=start
#include <stack>
#include <algorithm>
#include <string>
using namespace std;
//* 用栈
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
        while (!sta.empty()) {      //* 将栈中元素放到result字符串汇总
            result += sta.top();
            sta.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

//* 不用栈
class Solutin2 {
public:
    string removeDuplicates(string S) {
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

