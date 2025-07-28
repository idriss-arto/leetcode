/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 * 动态规划（不连续子序列）
 * [1143] 最长公共子序列
 */

/*
 * 此题求最长公共子序列，不要求连续
 *
 * 题解动态规划
 * 思路：
 * dp[i][j] ：只考虑下标i - 1之前元素的A，和只考虑下标j - 1之前的B，最长公共子序列长度为dp[i][j]。
 * 状态转移和下面一样
 * 这样写不用单独初始化
 * 
 * 我的思路：
 * dp[i][j]表示text1下标i之前，text2下标j之前，能满足的最长公共子序列（不要求连续）
 * if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
 * else dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 
 * 需要初始化第一行和第一列（这题初始化很麻烦）
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;

/*
 * Carl动态规划：
 * dp[i][j] ：只考虑下标i - 1之前元素的A，和只考虑下标j - 1之前的B，最长公共子序列长度为dp[i][j]。
 * 状态转移和下面一样
 * 这样写不用单独初始化
*/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {     //* 注意这里比较的是 text1[i - 1] 和 text2[j - 1]
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } 
                //! 和718.最长重复连续子序列不一样的地方
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

/*
 * 我的动态规划：
 * dp[i][j]表示text1下标i之前，text2下标j之前，能满足的最长公共子序列（不要求连续）
 * if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
 * else dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 
 * 需要初始化第一行和第一列
*/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));

        //* 初始化第一行和第一列
        for (int i = 0; i < text1.size(); i++) {
            if (text1[i] == text2[0] || (i > 0 && dp[i-1][0])) dp[i][0] = 1;
        }
        for (int j = 0; j < text2.size(); j++) {
            if (text1[0] == text2[j] || (j > 0 && dp[0][j-1])) dp[0][j] = 1;
        }

        for (int i = 1; i < text1.size(); i++) {
            for (int j = 1; j < text2.size(); j++) {
                if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
                //! 和718.最长重复连续子序列不一样的地方
                else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
        
        return dp.back().back();
    }
};
// @lc code=end

