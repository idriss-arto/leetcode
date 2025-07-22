/*
 * @lc app=leetcode.cn id=123 lang=cpp
 * 动态规划
 * [123] 买卖股票的最佳时机 III
 */

/*
 ! 限定买卖次数（两次）
 *
 * 动态规划思路：
 * 一天一共就有五个状态，
 * 0.没有操作 （其实我们也可以不设置这个状态）
 * 1.第一次持有股票
 * 2.第一次不持有股票
 * 3.第二次持有股票
 * 4.第二次不持有股票
 * 
 ! 注意，需要初始化dp[0][3] = -prices[0]，可考虑为第0天买入后马上卖出，再买入
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
        //! 注意这里dp[0][3]的初始化
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
 * dp[i][0].第一次持有股票
 * dp[i][1].第一次不持有股票
 * dp[i][2].第二次持有股票
 * dp[i][3].第二次不持有股票
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(4, 0));
        dp[0][0] = -prices[0];
        dp[0][2] = -prices[0];

        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], 0 - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
            
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] - prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] + prices[i]);
        }

        return dp[prices.size() - 1][3];
    }
};

/*
 * 官方题解，动态规划
 * 思路：无论题目中是否允许「在同一天买入并且卖出」这一操作，最终的答案都不会受到影响，这是因为这一操作带来的收益为零。
 * 例如，在计算 sell1 时，我们直接使用 buy1 而不是 buy1′ 进行转移。
 * buy1 比 buy1′ 多考虑的是在第 i 天买入股票的情况，
 * 而转移到 sell1 时，考虑的是在第 i 天卖出股票的情况，
 * 这样在同一天买入并且卖出收益为零，不会对答案产生影响。
 * 同理对于 buy2 以及 sell2 ，我们同样可以直接根据第 i 天而不是第 i-1 天计算出的值来进行状态转移。
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        int buy1 = -prices[0], sell1 = 0;
        int buy2 = -prices[0], sell2 = 0;
        for(int i = 1;i<n;i++){
            buy1 = max(buy1,-prices[i]);
            sell1 = max(sell1,buy1 + prices[i]);
            buy2 = max(buy2,sell1-prices[i]);
            sell2 = max(sell2,buy2 + prices[i]);
        }
        
        return sell2;
    }
};
// @lc code=end

