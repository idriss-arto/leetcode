/*
 * @lc app=leetcode.cn id=115 lang=cpp
 * 动态规划
 ! [115] 不同的子序列
 */

// @lc code=start
#include <string>
#include <vector>
#include <cstdint>
using namespace std;

/* 
 * 我的解法，动态规划
 * 思路：
 * 令dp[i][j]表示s以下标i-1为结尾的子字符串a，和t以下标j-1为结尾的子字符串b，a的子序列中b出现的个数
 * 也就是a中有dp[i][j]种方式删除特定元素构成b
 * 
 * 递推公式有两种情况：
 * 情况一：
 * s[i-1] == t[j-1]，此时a通过删除构成b可以选择 用s[i-1]匹配t[j-1] 或者 不用s[i-1]匹配t[j-1]
 * 用s[i-1]匹配t[j-1]，即删去下标i-1的a 通过删除构成 删去下标j-1的b 的方式数是dp[i-1][j-1]
 * 不用s[i-1]匹配t[j-1]，即删去下标i-1的a 通过删除构成 b 的方式数是dp[i-1][j]
 * 则dp[i][j] = dp[i-1][j] + dp[i-1][j-1]
 * 
 * 情况二：
 * s[i-1] != t[j-1]，此时a想通过删除构成b只能选择不用s[i-1]匹配t[j-1]
 * 则dp[i][j] = dp[i-1][j]
 * 
 ! 根据递推公式，边界为第一行和第一列，
 ! 第一行需初始化为0，即dp[0][j]表示 s前0个元素（空串） 通过删除构成 t前j个元素 的方式为0
 ! 第一列需初始化为1，即dp[i][0]表示 s前i个元素 通过删除构成 t前0个元素（空串） 的方式只有一种，即全删
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<vector<uint64_t>> dp(s.size()+1, vector<uint64_t>(t.size()+1, 0));

        //* 初始化
        for (int i = 0; i <= s.size(); i++) dp[i][0] = 1;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                dp[i][j] = dp[i-1][j];
                if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
            }
        }

        return dp.back().back();
    }
};
// @lc code=end

