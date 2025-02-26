/*
 * @lc app=leetcode.cn id=150 lang=cpp
 * 栈
 * [150] 逆波兰表达式求值
 */

// @lc code=start
#include <stack>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
int evalRPN(vector<string>& tokens) {
    // 力扣修改了后台测试数据，需要用longlong
    stack<long long> st; 
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            long long num1 = st.top();
            st.pop();
            long long num2 = st.top();
            st.pop();
            if (tokens[i] == "+") st.push(num2 + num1);
            if (tokens[i] == "-") st.push(num2 - num1);
            if (tokens[i] == "*") st.push(num2 * num1);
            if (tokens[i] == "/") st.push(num2 / num1);
        } 
        else {
            // 输入的不一定是个位数，用stoi或stoll函数直接转换比较好
            st.push(stoll(tokens[i]));
        }
    }

    long long result = st.top();
    st.pop(); // 把栈里最后一个元素弹出（其实不弹出也没事）
    return result;
}
};
// @lc code=end

