/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * 动态规划
 * [583] 两个字符串的删除操作
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;

/*
 * 我的动态规划
 * 思路：
 ! 求出最长公共子序列s，再间接求出word1和word2变为这个s所需要删除的字符数
 * 
 * 让dp[i][j]表示word1以下标i-1为尾的子序列s1，word2以下标j-1为尾的子序列s2，s1和s2的最长公共子序列为dp[i][j]
 * 
 * dp[i][j]的状态转移有两种情况
 * 一：word1[i-1] == word2[j-1]，则dp[i][j] = dp[i-1][j-1]+1;
 * 二：word1[i-1] != word2[j-1]，则dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
 * 
 * 注意，dp[word1.size()][word2.size()]不一定是最大值
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();
        vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
        int maxCnt = 0;

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

                maxCnt = max(maxCnt , dp[i][j]);
            }
        }

        return len1 + len2 - 2 * maxCnt;
    }
};

/*
 * Carl的动态规划
 * 思路：
 * 让dp[i][j]表示word1以下标i-1为尾的子序列s1，word2以下标j-1为尾的子序列s2，
 *              s1和s2想要相等，所需删除元素的最少次数
 * 
 * dp[i][j]的状态转移
 * 当word1[i - 1] 与 word2[j - 1]相同的时候，dp[i][j] = dp[i - 1][j - 1];
 * 
 * 当word1[i - 1] 与 word2[j - 1]不相同的时候，有三种情况：
 * 情况一：删word1[i - 1]，最少操作次数为dp[i - 1][j] + 1
 * 情况二：删word2[j - 1]，最少操作次数为dp[i][j - 1] + 1
 * 情况三：同时删word1[i - 1]和word2[j - 1]，操作的最少次数为dp[i - 1][j - 1] + 2
 * 最后取最小值，所以当word1[i - 1] 与 word2[j - 1]不相同的时候，
 * 递推公式：dp[i][j] = min({dp[i - 1][j - 1] + 2, dp[i - 1][j] + 1, dp[i][j - 1] + 1});
 * 
 * 初始化：
 * 根据状态转移方程，需要初始化第一行和第一列。显然dp[i][0]应该为i，dp[0][j]应该为j
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;

        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    //* 因为dp[i-1][j] = min(dp[i-1][j-1]+1, dp[i-2][j]+1, dp[i-2][j-1]+2) <= dp[i-1][j-1]+1
                    //* 所以dp[i-1][j]+1 <= dp[i-1][j-1]+2
                    //* 所以以下式子可化简为 dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1)
                    dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i-1][j-1] + 2);
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
// @lc code=end

