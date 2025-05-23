/*
 * @lc app=leetcode.cn id=123 lang=cpp
 * 动态规划
 * [123] 买卖股票的最佳时机 III
 */

/*
 * 限定买卖次数（两次）
 * 动态规划思路：
 * 一天一共就有五个状态，
 * 0.没有操作 （其实我们也可以不设置这个状态）
 * 1.第一次持有股票
 * 2.第一次不持有股票
 * 3.第二次持有股票
 * 4.第二次不持有股票
 ! 注意，需要初始化dp[0][3] = -prices[0]，可考虑为第0天买入后马上卖出，再买入
 * 
*/

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
/*
 * 动态规划
 * 一天一共就有五个状态，
 * dp[i][0].没有操作 （其实我们也可以不设置这个状态）
 * dp[i][1].第一次持有股票
 * dp[i][2].第一次不持有股票
 * dp[i][3].第二次持有股票
 * dp[i][4].第二次不持有股票
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
        dp[0][1] = -prices[0];
        dp[0][3] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            dp[i][2] = max(dp[i-1][2], dp[i-1][1] + prices[i]);
            dp[i][3] = max(dp[i-1][3], dp[i-1][2] - prices[i]);
            dp[i][4] = max(dp[i-1][4], dp[i-1][3] + prices[i]);
        }
        return dp[prices.size()-1][4];
    }
};

/*
 * 动态规划
 * 可以不设置状态0，即一天一共就有四个状态，
 * dp[i][0].第一次不持有股票
 * dp[i][1].第一次持有股票
 * dp[i][2].第二次不持有股票
 * dp[i][3].第二次持有股票
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(4, 0));
        dp[0][1] = -prices[0];
        dp[0][3] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], 0 - prices[i]);
            
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][3] + prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][0] - prices[i]);
        }
        return dp[prices.size() - 1][4];
    }
};
// @lc code=end

