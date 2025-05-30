/*
 * @lc app=leetcode.cn id=72 lang=cpp
 * 动态规划
 ! [72] 编辑距离
 */

/*
 * 思路：
 * dp[i][j] 表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]。
 * 
 * 
 * 
 * 状态转移方程确定：
 * if (word1[i - 1] == word2[j - 1]) 那么说明不用任何编辑，dp[i][j] 就应该是 dp[i - 1][j - 1]，即dp[i][j] = dp[i - 1][j - 1];
 * 
 * 
 * if (word1[i - 1] != word2[j - 1])，此时需要编辑了，有以下几种编辑方式
 * 
 * 操作一：word1删除一个元素，那么就是以下标i - 2为结尾的word1 与 j-1为结尾的word2的最近编辑距离 再加上一个操作。
 * 即 dp[i][j] = dp[i - 1][j] + 1;
 * 
 * 操作二：word2删除一个元素（word1增加一个等同于word2删除一个），那么就是以下标i - 1为结尾的word1 与 j-2为结尾的word2的最近编辑距离 再加上一个操作。
 * 即 dp[i][j] = dp[i][j - 1] + 1;
 * 
 * 操作三：替换元素，word1替换word1[i - 1]，使其与word2[j - 1]相同，此时不用增删加元素。
 * 那么只需要一次替换的操作，就可以让 word1[i - 1] 和 word2[j - 1] 相同。
 * 所以 dp[i][j] = dp[i - 1][j - 1] + 1;
 * 
 * 综上，当 if (word1[i - 1] != word2[j - 1]) 时取最小的，即：dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
 * 
 * 
 * 
 * 初始化：
 * dp[i][0] ：以下标i-1为结尾的字符串word1，和空字符串word2，最近编辑距离为dp[i][0]。
 * 那么dp[i][0]就应该是i，也就是word1里的元素全部做删除操作，即：dp[i][0] = i;
 * 同理dp[0][j] = j;
*/

// @lc code=start
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));

        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;

        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    //* 注意这里min函数的用法，现将多个元素拼成一个初始化列表，再传入min函数
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
// @lc code=end

