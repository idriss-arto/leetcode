// @lc code=start
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<vector<int>> dp(s.size()+1, vector<int>(t.size()+1, 0));

        for (int i = 0; i <= s.size(); i++) dp[i][0] = 1;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                dp[i][j] = dp[i-1][j];
                if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
            }
        }

        for (int i = 0; i <= s.size(); i++) {
            for (int j = 0; j <= t.size(); j++) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }

        return dp.back().back();
    }
};

int main() {
    Solution a;
    string s = "babgbag";
    string t = "bag";
    a.numDistinct(s, t);
    return 0;
}
// @lc code=end

