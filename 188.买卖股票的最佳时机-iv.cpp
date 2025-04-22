/*
 * @lc app=leetcode.cn id=188 lang=cpp
 * 动态规划
 * [188] 买卖股票的最佳时机 IV
 */

/*
 * 限定买卖次数（k次）
 * 动态规划思路：
 * dp[i][j] ：第i天的状态为j，所剩下的最大现金是dp[i][j]
 * 一天一共就有2*k+1个状态，
 * 0.没有操作 （其实我们也可以不设置这个状态）
 * 1.第一次持有股票
 * 2.第一次不持有股票
 * 3.第二次持有股票
 * 4.第二次不持有股票
 * 以此类推
 ! 注意，需要初始化dp[0][2*n+1] = -prices[0]（0 <= n < k），可考虑为第0天买入后马上卖出，再买入
*/ 

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2*k+1, 0));
        for (int i = 1; i < 2*k; i+=2) {
            dp[0][i] = -prices[0];
        }

        for (int i = 1; i < prices.size(); i++) {
            for (int j = 1; j < 2*k; j+=2) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] - prices[i]);
                dp[i][j+1] = max(dp[i-1][j+1], dp[i-1][j] + prices[i]);
            }
        }

        return dp[prices.size()-1][2*k];
    }
};
// @lc code=end

