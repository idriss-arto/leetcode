/*
 * @lc app=leetcode.cn id=139 lang=cpp
 * 动态规划（完美背包）
 * [139] 单词拆分
 */

/*
 * 思路：
 ! 此题隐含求排列数，遍历时背包必须在外层
 * 用dp[i]为true表示下标i之前的字母组成的字符串可以拆分为字典中单词的累积，
 * 所以判断dp[i]是否为true时，
 * 需要遍历j从i-1到0，判断dp[j]是否为true，以及从j到i-1（左闭右闭）的子串是否在字典中。
 * 
 * 我的思路是写一个比较函数cmp，每次要判断子串是否在字典中时传入子串，和字典中的字符串一个个比
 * 题解的思路是用unordered_set重新装字典，这样要判断时直接用find即可，不用再在比较函数里一个个比
*/

// @lc code=start
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

//* dp[i]为true表示以第i个字母结尾的子串可以拆分为字典中单词的累积
//! 此题隐含求排列数，遍历时背包必须在外层
class Solution {
public:
    bool cmp(string subS, vector<string>& wordDict) {
        for (int i = 0; i < wordDict.size(); i++) {
            if (subS.compare(wordDict[i]) == 0) return true;
        }
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length() + 1, false);

        //* 初始化
        dp[0] = true;

        for (int i = 1; i <= s.length(); i++) {
            for (int j = i; j >= 1; j--) {
                //* 先判断第j个字母之前的字符串能不能拆分
                if (dp[j-1] == true) {
                    //* 再判断第j个字母到第i个字母能不能匹配字典中任一单词
                    dp[i] = cmp(s.substr(j-1, i-j+1), wordDict);
                    if (dp[i]) break;
                }
            }
        }

        return dp[s.length()];
    }
};

//* 题解解法，用unordered_set重新装wordDict，提高对比速度
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //* 用unordered_set替代比较函数，不用再一个个比，直接用find
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++) {       //* 遍历背包
            for (int j = 1; j <= i; j++) {           //* 遍历物品
                string word = s.substr(j - 1, i - j + 1);   //* substr(起始位置，截取的个数)
                if (dp[j - 1] && wordSet.find(word) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};
// @lc code=end

