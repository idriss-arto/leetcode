/*
 * @lc app=leetcode.cn id=516 lang=cpp
 * 动态规划
 * [516] 最长回文子序列
 */

/*
 * 动态规划思路：
 * dp[i][j]：字符串s在[i, j]范围内最长的回文子序列的长度为dp[i][j]。
 * 
 * 状态转移方程：
 * 如果s[i]与s[j]相同，那么dp[i][j] = dp[i + 1][j - 1] + 2;
 * 
 * 如果s[i]与s[j]不相同，说明s[i]和s[j]的同时加入 并不能增加[i,j]区间回文子序列的长度，那么分别加入s[i]、s[j]看看哪一个可以组成最长的回文子序列。
 * 加入s[j]的回文子序列长度为dp[i + 1][j]。
 * 加入s[i]的回文子序列长度为dp[i][j - 1]。
 * 那么dp[i][j]一定是取最大的，即：dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
*/

// @lc code=start
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        for (int i = 0; i < s.size(); i++) dp[i][i] = 1;

        //! 注意这里外层遍历顺序是从下往上
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
// @lc code=end

