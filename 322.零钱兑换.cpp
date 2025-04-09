/*
 * @lc app=leetcode.cn id=322 lang=cpp
 * 动态规划（完全背包）
 * [322] 零钱兑换
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
//* dp[i]表示组成金额i所需的最少硬币数
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, __INT_MAX__);

        dp[0] = 0;

        //* 所求值与元素排列顺序无关（既不是求组合数，也不是求排列数），所以可以调换内外循环顺序
        for (int i = 0; i < coins.size(); i++) {                //* 外层遍历物品
            for (int j = coins[i]; j <= amount; j++) {          //* 内层遍历背包容量
                //* 如果dp[j - coins[i]]是初始值则跳过
                if (dp[j - coins[i]] != __INT_MAX__) dp[j] = min(dp[j], dp[j-coins[i]] + 1);
            }
        }
        return (dp[amount] != __INT_MAX__) ? dp[amount] : -1;
    }
};
// @lc code=end

