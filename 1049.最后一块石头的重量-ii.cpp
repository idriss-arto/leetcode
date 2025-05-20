/*
 * @lc app=leetcode.cn id=1049 lang=cpp
 * 动态规划
 ! [1049] 最后一块石头的重量 II
 */

/*
 * 给定背包容量，尽可能地装，最多能装多少
 * 
 * 思路
 ! 本题其实是尽量让石头分成重量相同的两堆（尽可能相同），相撞之后剩下的石头就是最小的。
 * 一堆的石头重量是sum，那么我们就尽可能拼成重量为sum / 2 的石头堆。 
 * 这样剩下的石头堆也是尽可能接近 sum/2 的重量。 
 * 那么此时问题就是有一堆石头，每个石头都有自己的重量，是否可以装满最大重量为sum / 2的背包。
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for (int& i : stones) {
            sum += i; 
        }
        int target = sum / 2;
        
        /*
         * 01背包，二维dp数组版本
        vector<vector<int>> dp(stones.size(), vector<int>(target + 1, 0));
        for (int j = stones[0]; j <= target; j++) {
            dp[0][j] = stones[0];
        }
        for (int i = 1; i < stones.size(); i++) {
            for (int j = 1; j <= target; j++) {
                if (j < stones[i]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j - stones[i]] + stones[i]);
                }
            }
        }

        return sum - dp[stones.size() - 1][target] * 2;
        */

        //* 01背包，滚动dp数组写法
        vector<int> dp(target+1, 0);
        for (int i = 0; i < stones.size(); i++) {
            //* 注意遍历背包容量是从大到小，且只遍历到当前物品容量
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        
        return sum - dp[target] * 2;
    }
};
// @lc code=end

