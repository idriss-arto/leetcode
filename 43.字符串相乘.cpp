/*
 * @lc app=leetcode.cn id=43 lang=cpp
 * 字符串
 ! [43] 字符串相乘
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        int l1 = num1.size();
        int l2 = num2.size();

        //! 令 m 和 n 分别表示 num1 和 num2 的长度，并且它们均不为 0，
        //! 则 num1 和 num2 的乘积的长度为 m+n−1 或 m+n。
        vector<int> temp(l1 + l2, 0);


        for (int i = l1 - 1; i>= 0; --i) {
            for (int j = l2 - 1; j >= 0; --j) {
                //! 下标从1开始算的话，num1从左往右第i位 和 num2从左往右第j位 相乘的位置应放在 temp从左往右第i+j位 上
                //! 所以 num1[i]（第i+1位） 和 num2[j]（第j+1位） 相乘的位置应放在 temp[i + j + 1]（第i+j+2位） 上 
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + temp[i + j + 1];
                temp[i + j + 1] = sum % 10;
                temp[i + j] += sum / 10;             //* 进位
            }
        }

        string res;
        for (int i = 0; i < l1 + l2; i++) {
            if (temp[i] == 0 && res.empty()) {
                continue;
            }
            res.push_back(temp[i] + '0');
        }

        return res;
    }
};
// @lc code=end

