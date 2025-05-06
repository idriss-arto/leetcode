/*
 * @lc app=leetcode.cn id=392 lang=cpp
 * 双指针，动态规划（非连续子序列）
 * [392] 判断子序列
 */

/*
 * 只有一个s判断是不是t子序列时
 * 两个解法：双指针，动态规划
 * 
 * 进阶：有很多个s分别判断是不是t子序列时
 * 解法：预处理+动态规划
 * 
 * 具体思路见下
*/

// @lc code=start
#include <string>
#include <vector>
using namespace std;
//* 我的解法一，双指针
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sp = 0, tp = 0;
        while (sp < s.size() && tp < t.size()) {
            if (s[sp] == t[tp]) sp++;
            tp++;
        }
        if (sp == s.size()) return true;
        else return false; 
    }
};

/*
 * 我的解法二，动态规划
 * 思路：
 * 让dp[i][j]表示s前i个字母（即下标i-1及之前）是否是t前j个字母（即下标j-1及之前）的子序列
 * 则dp[i][j]为true，有两种情况
 * 情况一：dp[i][j-1]就为true
 * 情况二：s[i-1]==t[j-1]且dp[i-1][j-1]为true
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<bool>> dp(s.size()+1, vector<bool>(t.size()+1, false));
        for (int j = 0; j <= t.size(); j++) dp[0][j] = true;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (dp[i][j-1]) dp[i][j] = true;
                else if (s[i-1] == t[j-1] && dp[i-1][j-1]) dp[i][j] = true;
            }
        }

        return dp[s.size()][t.size()];
    }
};

/*
 * Carl题解，动态规划
 * 思路：
 * dp[i][j] 表示以下标i-1为结尾的字符串s，和以下标j-1为结尾的字符串t，相同子序列的长度为dp[i][j]
 * 递推公式有两种情况：
 * 情况一：
 * if (s[i - 1] == t[j - 1])，那么dp[i][j] = dp[i - 1][j - 1] + 1;，
 * 因为找到了一个相同的字符，相同子序列长度自然要在dp[i-1][j-1]的基础上加1
 * 
 * 情况二：
 * if (s[i - 1] != t[j - 1])，此时相当于t要删除元素，t如果把当前元素t[j - 1]删除，
 * 那么dp[i][j] 的数值就是 看s[i - 1]与 t[j - 2]的比较结果了，即：dp[i][j] = dp[i][j - 1];
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = dp[i][j - 1];
            }
        }
        if (dp[s.size()][t.size()] == s.size()) return true;
        return false;
    }
};

/*
 * 官方题解，动态规划
 * 可用来应对进阶问题，即s有很多个，分别判断是不是t的子序列
 * 思路：
 * 预处理出对于 t 的每一个位置，从该位置开始往后每一个字符第一次出现的位置。
 * dp[pos_i][alp_j] 表示字符串 t 中从下标 pos_i 开始往后（包括下标pos_i），字符 alp_j 第一次出现的下标。
 * 
 * 递推公式有两种情况：
 * 情况一：
 * 如果 t 中下标 pos_i 的字符就是 alp_j，那么 dp[pos_i][alp_j] = pos_i
 * 
 * 情况二：
 * 如果 t 中下标 pos_i 的字符不是 alp_j，则 alp_j 出现在下标 pos_i+1 开始往后，
 * 即 dp[pos_i][alp_j] = dp[pos_i+1][alp_j]
 * 
 * 从递推公式可以看出需要从后往前遍历pos_i
 * 
 * 那么边界情况就是dp[t.size()][alp_j]，将其置为t.size()，
 * 这样dp[pos_i][alp_j]为 t.size() 表示下标pos_i及以后不存在字符j
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.size(), m = t.size();

        vector<vector<int> > dp(m + 1, vector<int>(26, 0));
        //* 初始化
        for (int alp_j = 0; alp_j < 26; alp_j++) {
            dp[m][alp_j] = m;
        }

        //! 预处理
        for (int pos_i = m - 1; pos_i >= 0; pos_i--) {
            for (int alp_j = 0; alp_j < 26; alp_j++) {
                if (t[pos_i] == alp_j + 'a')
                    dp[pos_i][alp_j] = pos_i;
                else
                    dp[pos_i][alp_j] = dp[pos_i + 1][alp_j];
            }
        }

        //* 使用预处理的结果
        int pos = 0;
        for (int i = 0; i < n; i++) {
            if (dp[pos][s[i] - 'a'] == m) {
                return false;
            }
            pos = dp[pos][s[i] - 'a'] + 1;
        }
        return true;
    }
};
// @lc code=end

