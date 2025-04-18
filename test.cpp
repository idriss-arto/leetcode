/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start

#include <vector>
#include <stdio.h>
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        vector<bool> flag(nums.size(), false);
        dp[0] = nums[0];
        flag[0] = true;
        if (nums[0] > nums[1]) {
            dp[1] = nums[0];
            flag[1] = true;
        }
        else dp[1] = nums[1];
        for (int i = 2; i < nums.size(); i++) {
            if (i == nums.size() - 1) {
                if (flag[i-1] && flag[i-2]) {
                    if (nums[i] > nums[0]) {
                        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]) - nums[0];
                    }
                    else {
                        dp[i] = dp[i - 1];
                    }
                }
                else if (!flag[i-1] && flag[i-2]) {
                    if (nums[i] > nums[0]) {
                        dp[i] = max(dp[i - 2] + nums[i] - nums[0], dp[i - 1]);
                    }
                    else {
                        dp[i] = dp[i - 1];
                    }
                }
                else {
                    dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
                }
            }
            else {
                if (dp[i - 2] + nums[i] > dp[i - 1]) {
                    dp[i] = dp[i - 2] + nums[i];
                    flag[i] = flag[i - 2];
                }
                else {
                    dp[i] = dp[i - 1];
                    flag[i] = flag[i - 1];
                }
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            printf("dp[%d]:%d\n", i, dp[i]);
        }

        return dp[nums.size() - 1];
    }
};

int main() {
    Solution s;
    vector<int> x = {2,2,4,3,2,5};
    s.rob(x);
    return 0;
}
// @lc code=end

