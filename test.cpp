// @lc code=start
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
        for (int i = 0; i < text1.size(); i++) {
            if (text1[i] == text2[0] || (i > 0 && dp[i-1][0])) dp[i][0] = 1;
        }
        for (int j = 0; j < text2.size(); j++) {
            if (text1[0] == text2[j] || (j > 0 && dp[0][j-1])) dp[0][j] = 1;
        }

        for (int i = 1; i < text1.size(); i++) {
            for (int j = 1; j < text2.size(); j++) {
                if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
            }
        }
        for (int i = 0; i < text1.size(); i++) {
            for (int j = 0; j < text2.size(); j++) {
                printf("%2d ", dp[i][j]);
            }
            printf("\n");
        }
        
        return dp.back().back();
    }
};

int main() {
    Solution s;
    string s1 = "abcde";
    string s2 = "ace";
    s.longestCommonSubsequence(s1, s2);
    return 0;
}
// @lc code=end

