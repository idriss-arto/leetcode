/*
 * @lc app=leetcode.cn id=139 lang=cpp
 * 动态规划（完美背包）
 * [139] 单词拆分
 */

// @lc code=start
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
class Solution {
//* dp[i]为true表示下标i及之前的字母组成的字符串可以拆分为字典中单词的累积
//* 此题隐含求排列数，遍历时背包必须在外层
public:
    bool cmp(string subS, vector<string>& wordDict) {
        for (int i = 0; i < wordDict.size(); i++) {
            if (subS.compare(wordDict[i]) == 0) return true;
        }
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length() + 1, false);

        dp[0] = true;

        for (int i = 1; i <= s.length(); i++) {
            for (int j = i-1; j >= 0; j--) {
                if (dp[j] == true) {
                    dp[i] = cmp(s.substr(j, i-j), wordDict);
                    if (dp[i]) break;
                }
            }
        }

        return dp[s.length()];
    }
};

//* 题解解法，用unordered_set重新装wordSet，提高对比速度
class Solution2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {       //* 遍历背包
            for (int j = 0; j < i; j++) {           //* 遍历物品
                string word = s.substr(j, i - j);   //* substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
// @lc code=end

