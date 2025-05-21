/*
 * @lc app=leetcode.cn id=518 lang=cpp
 * 动态规划（完全背包（求组合数））
 ! [518] 零钱兑换 II
 */

//* 求组合数

// @lc code=start
#include <vector>
using namespace std;

//* 滚动数组版本
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //* dp[j]表示组成数字j的方式
        vector<unsigned long long> dp(amount+1, 0);

        dp[0] = 1;

        //! 注意，这里不能调换循环顺序，因为是求组合数，调换后变成求排列数
        //! 解释见 https://programmercarl.com/0518.%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2II.html#%E4%B8%80%E7%BB%B4dp%E8%AE%B2%E8%A7%A3
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] += dp[j-coins[i]];
            }
        }

        return dp[amount];
    }
};

//* 二维数组版本
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //* dp[i][j]表示前i个数组成数字j的方式
        vector<vector<unsigned long long>> dp(coins.size(), vector<unsigned long long>(amount+1, 0));

        //* 注意组成0的方式固定为1（因为coins[i]大于0），即第一列固定为1
        for (int i = 0; i < coins.size(); i++) {
            dp[i][0] = 1;
        }

        for (int j = coins[0]; j <= amount; j += coins[0]) {
            dp[0][j] = dp[0][j-coins[0]];
        }

        //! 求组合方式数时，遍历顺序行列可以颠倒
        //! 换句话说，二维数组只能用来求组合方式数，不能求排列方式数
        for (int i = 1; i < coins.size(); i++) {    //* 行，遍历物品
            for (int j = 0; j <= amount; j++) {     //* 列，遍历背包容量
                if (j < coins[i]) dp[i][j] = dp[i-1][j];
                else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
                    /*
                     * 等价于以下代码，但效率更高
                    int k = j;
                    while (k >= 0) {
                        dp[i][j] += dp[i-1][k];
                        k -= coins[i];
                    }
                    */
                }
            }
        }

        return dp[coins.size()-1][amount];
    }
};
// @lc code=end

