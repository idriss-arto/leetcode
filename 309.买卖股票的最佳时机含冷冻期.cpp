/*
 * @lc app=leetcode.cn id=309 lang=cpp
 * 动态规划
 ! [309] 买卖股票的最佳时机含冷冻期
 */

/*
 ! 不限定买卖次数，有买卖冷静期（1天）
 *
 * 我的动态规划思路：
 * dp[i][j] ：第i天的状态为j的情况下，所剩下的最大现金是dp[i][j]
 * 一天一共就有3个状态，
 * 0.不持有股票（卖出之后第二天(不准买那一天)及以后）
 * 1.持有股票
 * 2.卖出当天
 * 
 * 
 * 题解的动态规划思路：
 * 0：买入状态；1：卖出状态；2：今天卖出；3：冷冻状态
 * 见图片文件309
*/ 

// @lc code=start
#include <vector>
using namespace std;

/*
 * 我的动态规划思路：
 * dp[i][j] ：第i天的状态为j的情况下，所剩下的最大现金是dp[i][j]
 * 一天一共就有3个状态，
 * 0.不持有股票（卖出之后第二天(不准买那一天)及以后）
 * 1.持有股票
 * 2.卖出当天
 */ 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 1) return 0; 

        vector<vector<int>> dp(prices.size(), vector<int>(3, 0));
        dp[0][1] = -prices[0];

        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][2]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            dp[i][2] = max(dp[i-1][2], dp[i-1][1] + prices[i]);
        }

        //* 注意这里返回的是最后一天两个状态里的较大值
        return max(dp[prices.size()-1][0], dp[prices.size()-1][2]);
    }
};

//* Carl题解解法
//* 0：买入状态；1：卖出状态；2：今天卖出；3：冷冻状态
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) return 0;

        vector<vector<int>> dp(n, vector<int>(4, 0));
        dp[0][0] -= prices[0];

        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][0] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }

        //* 注意这里返回的是最后一天两个状态里的较大值
        return max(dp[n - 1][3], max(dp[n - 1][1], dp[n - 1][2]));
    }
};
// @lc code=end

