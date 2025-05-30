/*
 * @lc app=leetcode.cn id=122 lang=cpp
 * 贪心，动态规划
 * [122] 买卖股票的最佳时机 II
 */

/*
 ! 可多次买卖（不带冷静期）
 *
 * 贪心思路：
 * 第 0 天买入，第 3 天卖出，那么利润为：prices[3] - prices[0]。
 ! 相当于(prices[3] - prices[2]) + (prices[2] - prices[1]) + (prices[1] - prices[0])。
 * 
 * 
 * 动态规划思路：
 * dp[i][0] 表示第i天不持有股票所得最多现金，dp[i][1] 表示第i天持有股票所得最多现金
 * 
 * 如果第i天不持有股票即dp[i][0]， 也可以由两个状态推出来
 * 第i-1天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp[i - 1][0]
 * 第i天卖出股票，所得现金就是按照今天股票价格卖出后所得现金即：dp[i - 1][1] + prices[i]
 * dp[i][0]取最大的，即dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + prices[i];
 * 
 * 如果第i天持有股票即dp[i][1]， 那么可以由两个状态推出来
 * 第i-1天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp[i - 1][1]
 * 第i天买入股票，所得现金就是第i-1天不持有的现金减去买入今天的股票后剩下的现金即：dp[i-1][0] - prices[i]
 * （注意第i天买入股票的情况，所得现金的式子和只能买卖一次的对应式子不一样）
 * dp[i][1]应该选所得现金最大的，所以dp[i][1] = max(dp[i - 1][1], dp[i-1][0] - prices[i]);
*/

// @lc code=start
#include <vector>
#include <climits>
#include <tuple>
using namespace std;

//* 动态规划(tie)
//* sell 表示不持有股票所得最多现金，buy 表示第i天持有股票所得最多现金
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 0) return 0;

        int sell = 0, buy = -prices[0];
        for (int i = 1; i < len; i++) {
            //* 不能用pair(sell, buy)
            tie(sell, buy) = make_pair(max(sell, buy + prices[i]), max(buy, -prices[i]));
        }

        return sell;
    }
};

//* 动态规划
//* dp[i][0] 表示第i天不持有股票所得最多现金，dp[i][1] 表示第i天持有股票所得最多现金
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][1] = -prices[0];

        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }

        return dp[prices.size()-1][0];
    }
};

//* 动态规划(滚动数组)
//* dp[i][0] 表示第i天不持有股票所得最多现金，dp[i][1] 表示第i天持有股票所得最多现金
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(2, vector<int>(2));  //* 注意这里只开辟了一个2 * 2大小的二维数组
        dp[0][1] -= prices[0];
        dp[0][0] = 0;

        for (int i = 1; i < len; i++) {
            dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][0] - prices[i]);
            dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] + prices[i]);
        }

        return dp[(len - 1) % 2][0];
    }
};

//* 贪心
//* 假如第 0 天买入，第 3 天卖出，那么利润为：prices[3] - prices[0]。
//! 相当于(prices[3] - prices[2]) + (prices[2] - prices[1]) + (prices[1] - prices[0])。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int income = 0;

        for (int i = 1; i < prices.size(); i++) {
            int n = prices[i] - prices[i - 1];
            if (n > 0) income += n;
        }
        
        return income;
    }
};
// @lc code=end

