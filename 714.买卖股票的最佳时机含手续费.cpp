/*
 * @lc app=leetcode.cn id=714 lang=cpp
 * 动态规划
 * [714] 买卖股票的最佳时机含手续费
 */

/*
 ! 不限交易次数，无冷静期，但有交易费
 * 思路一：动态规划，将手续费放在卖出时进行计算
 * 思路二：贪心，将手续费放在买入时进行计算
*/

// @lc code=start
#include <vector>
#include <tuple>
using namespace std;

//* 官方题解动态规划，将手续费放在卖出时进行计算
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

/*
 * 官方题解贪心，将手续费放在买入时进行计算
 * 当我们卖出一支股票时，我们就立即获得了以相同价格并且免除手续费买入一支股票的权利。
 * 我们用 buy 表示在最大化收益的前提下，如果我们手上拥有一支股票，那么它的最低买入价格是多少。
 * 在初始时，buy 的值为 prices[0] 加上手续费 fee。那么当我们遍历到第 i (i>0) 天时：
 * 1.
 * 如果当前的股票价格 prices[i] 加上手续费 fee 小于 buy，
 * 那么与其使用 buy 的价格购买股票，我们不如以 prices[i]+fee 的价格购买股票，
 * 因此我们将 buy 更新为 prices[i]+fee。
 * 
 * 2.
 * 如果当前的股票价格 prices[i] 大于 buy，
 * 那么我们直接卖出股票并且获得 prices[i]−buy 的收益。
 * 但实际上，我们此时卖出股票可能并不是全局最优的（例如下一天股票价格继续上升），
 * 因此我们可以提供一个反悔操作，看成当前手上拥有一支买入价格为 prices[i] 的股票，将 buy 更新为 prices[i]。
 * 这样一来，如果下一天股票价格继续上升，我们会获得 prices[i+1]−prices[i] 的收益，
 * 加上这一天 prices[i]−buy 的收益，恰好就等于在这一天不进行任何操作，而在下一天卖出股票的收益。
 * 
 * 3.
 * 对于其余的情况，prices[i] 落在区间 [buy−fee,buy] 内，
 * 它的价格没有低到我们放弃手上的股票去选择它，也没有高到我们可以通过卖出获得收益，因此我们不进行任何操作。
 * 
 * 不好理解
*/ 
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
// @lc code=end

