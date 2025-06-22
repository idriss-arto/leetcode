/*
 * @lc app=leetcode.cn id=394 lang=cpp
 * 栈
 * [394] 字符串解码
 */

// @lc code=start
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

//* 我的解法
//* 原字符串压入栈再处理，相当于原字符串从右往左处理
class Solution {
private:
    stack<char> sta;

    //* 处理完方括号里的内容，需要紧跟着处理方括号前的数字
    int decodeNum() {
        string num_str = "";
        while(!sta.empty()) {
            char x = sta.top();
            //* 注意这里读取top后没有第一时间pop
            if (x >= '0' && x <= '9') {             //* 可以用isdigit(x)判断是否为数字
                num_str.insert(num_str.begin(), x);
                sta.pop();
            }
            else break;
        }
        return stoi(num_str);
    }

    //* 处理方括号里的内容
    string decodePart() {
        //* 记录方括号里的内容解码的结果
        string part_result = "";
        while (!sta.empty()) {
            char x = sta.top();
            sta.pop();
            //* 普通内容直接加在part_result的最前面
            if (x >= 'a' && x <= 'z') {             //* 可以用islower(x)判断是否是小写字母，或isalpha(x)判断是否为字母
                part_result.insert(part_result.begin(), x);
            }
            //* 方括号里可能还有方括号，需要递归处理
            else if (x == ']'){
                string repeatPart = decodePart();
                int cnt = decodeNum();
                while (cnt--) {
                    part_result = repeatPart + part_result;
                }
            }
            else break;
        }
        //* 返回方括号内容解码的结果（内部不再有数字和方括号）
        return part_result;
    }

public:
    string decodeString(string s) {
        for (int i = 0; i < s.size(); i++) {
            sta.push(s[i]);
        }

        return decodePart();
    }
};

//* 题解解法
//* 原字符串从左往右处理
class Solution {
public:
    string getDigits(string &s, size_t &ptr) {
        string ret = "";
        while (isdigit(s[ptr])) {
            ret.push_back(s[ptr++]);
        }
        return ret;
    }

    string getString(vector <string> &v) {
        string ret;
        for (const auto &s: v) {
            ret += s;
        }
        return ret;
    }

    string decodeString(string s) {
        vector <string> stk;
        size_t ptr = 0;

        while (ptr < s.size()) {
            char cur = s[ptr];
            if (isdigit(cur)) {
                //* 获取一个数字并进栈
                string digits = getDigits(s, ptr);
                stk.push_back(digits);
            } else if (isalpha(cur) || cur == '[') {
                //* 获取一个字母并进栈
                stk.push_back(string(1, s[ptr++])); 
            } else {
                ++ptr;
                vector <string> sub;
                while (stk.back() != "[") {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                reverse(sub.begin(), sub.end());
                //* 左括号出栈
                stk.pop_back();
                //* 此时栈顶为当前 sub 对应的字符串应该出现的次数
                int repTime = stoi(stk.back()); 
                stk.pop_back();
                string t, o = getString(sub);
                //* 构造字符串
                while (repTime--) t += o; 
                //* 将构造好的字符串入栈
                stk.push_back(t);
            }
        }

        return getString(stk);
    }
};
// @lc code=end

