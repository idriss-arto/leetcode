/*
 * @lc app=leetcode.cn id=714 lang=cpp
 * 动态规划
 * [714] 买卖股票的最佳时机含手续费
 */

/*
 * 不限交易次数，无冷静期，但有交易费
*/

// @lc code=start
#include <vector>
#include <tuple>
using namespace std;
//* 题解动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int sell = 0, buy = -prices[0];
        for (int i = 1; i < n; ++i) {
            //* 不能用pair(sell, buy)
            tie(sell, buy) = make_pair(max(sell, buy + prices[i] - fee), max(buy, sell - prices[i]));
        }
        return sell;
    }
};

//* 题解贪心
//* 当我们卖出一支股票时，我们就立即获得了以相同价格并且免除手续费买入一支股票的权利。
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int buy = prices[0] + fee;
        int profit = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] + fee < buy) {
                buy = prices[i] + fee;
            }
            else if (prices[i] > buy) {
                profit += prices[i] - buy;
                buy = prices[i];
            }
        }
        return profit;
    }
};

//* 我的动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }
        return dp[prices.size()-1][0];
    }
};
// @lc code=end

