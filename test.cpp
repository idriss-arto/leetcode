/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;
class Solution {
//* dp[i]为true表示前i个字母组成的字符串可以拆分为字典中单词的累积
public:
    bool cmp(string subS, vector<string>& wordDict) {
        for (int i = 0; i < wordDict.size(); i++) {
            if (subS.compare(wordDict[i]) == 0) return true;
        }
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length() - 1, false);

        for (int i = 0; i < s.length(); i++) {
            if (dp[i] == false) {
                printf("before dp[%d] = false\n", i);
            }
        }

        dp[0] = cmp(s.substr(0, 1), wordDict);

        for (int i = 1; i < s.length(); i++) {
            for (int j = i-1; j >= 0; j--) {
                if (j == 0) {
                    if (dp[0]) {
                        string subS = s.substr(1, i);
                        if (cmp(subS, wordDict)) dp[i] = true;
                    }
                    string subS = s.substr(0, i+1);
                    if (cmp(subS, wordDict)) dp[i] = true;
                }
                else if (dp[j] == true) {
                    string subS = s.substr(j+1, i-j);
                    if (cmp(subS, wordDict)) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < s.length(); i++) {
            if (dp[i]) {
                printf("dp[%d] = true\n", i);
            }
        }
        
        return dp[s.length() - 1];
    }
};

int main() {
    Solution s;
    string s1 = "ab";
    vector<string> wordDict = {"a", "b"};
    s.wordBreak(s1, wordDict);
    return 0;
}
// @lc code=end

