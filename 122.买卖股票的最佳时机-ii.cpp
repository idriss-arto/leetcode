/*
 * @lc app=leetcode.cn id=122 lang=cpp
 * 贪心或动态规划
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
//* 贪心
/*
 * 假如第 0 天买入，第 3 天卖出，那么利润为：prices[3] - prices[0]。
 * 相当于(prices[3] - prices[2]) + (prices[2] - prices[1]) + (prices[1] - prices[0])。
*/
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

