/*
 * @lc app=leetcode.cn id=32 lang=cpp
 * 动态规划，栈，计数器
 ! [32] 最长有效括号
 */

// @lc code=start
#include <string>
#include <vector>
#include <stack>
using namespace std;

/*
 * 定义 dp[i] 表示以下标 i 字符结尾的最长有效括号的长度
 * 1.
 * s[i]=')' 且 s[i−1]='('，也就是字符串形如 "……()"，我们可以推出：dp[i]=dp[i−2]+2
 * 
 * 2.
 * s[i]=')' 且 s[i−1]=')'，也就是字符串形如 “……))”，我们可以推出：
 ! 如果 s[i−dp[i−1]−1]='('，那么dp[i] = dp[i−1]+dp[i−dp[i−1]−2]+2
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } 
                else if (i - 1 - dp[i - 1] > 0 && s[i - 1 - dp[i - 1]] == '(') {    //* 注意边界处理
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - 1 - dp[i - 1] - 1] : 0) + 2;
                }
                maxans = max(maxans, dp[i]);
            }
        }
        return maxans;
    }
};

/*
 * 始终保持栈底元素为当前已经遍历过的元素中「最后一个没有被匹配的右括号的下标」，
 * 栈里其他元素维护左括号的下标：
 * 1.
 * 对于遇到的每个 ‘(’ ，我们将它的下标放入栈中
 * 2.
 * 对于遇到的每个 ‘)’ ，我们先弹出栈顶元素表示匹配了当前右括号：
 * 如果栈为空，说明当前的右括号为没有被匹配的右括号，我们将其下标放入栈中来更新我们之前提到的「最后一个没有被匹配的右括号的下标」
 * 如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」
 * 需要注意的是，在一开始的时候往栈中放入一个值为 −1 的元素。
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    maxans = max(maxans, i - stk.top());
                }
            }
        }
        return maxans;
    }
};

/*
 * 利用两个计数器 left 和 right
 * 首先，我们从左到右遍历字符串，
 * 对于遇到的每个 '('，我们增加 left 计数器，对于遇到的每个 ')' ，我们增加 right 计数器。
 * 每当 left 计数器与 right 计数器相等时，我们计算当前有效字符串的长度，并且记录目前为止找到的最长子字符串。
 * 当 right 计数器比 left 计数器大时，我们将 left 和 right 计数器同时变回 0。
 * 
 ! 贪心地考虑了以当前字符下标结尾的有效括号长度，每次当右括号数量多于左括号数量的时候之前的字符我们都扔掉不再考虑，
 ! 重新从下一个字符开始计算，但这样会漏掉一种情况，就是遍历的时候左括号的数量始终大于右括号的数量，即 (() ，这种时候最长有效括号是求不出来的
 * 
 * 所以，增加一次从右到左的遍历：
 * 对于遇到的每个 '('，我们增加 left 计数器，对于遇到的每个 ')' ，我们增加 right 计数器。
 * 每当 right 计数器与 left 计数器相等时，我们计算当前有效字符串的长度，并且记录目前为止找到的最长子字符串。
 * 当 left 计数器比 right 计数器大时，我们将 left 和 right 计数器同时变回 0。
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0, right = 0, maxlength = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = max(maxlength, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        left = right = 0;
        for (int i = (int)s.length() - 1; i >= 0; i--) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = max(maxlength, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        return maxlength;
    }
};
// @lc code=end

