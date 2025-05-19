/*
 * @lc app=leetcode.cn id=96 lang=cpp
 * 动态规划
 ! [96] 不同的二叉搜索树
 */

/*
 * 1.确定dp数组（dp table）以及下标的含义
 * dp[i] ： 1到i为节点组成的二叉搜索树的个数为dp[i]。
 * 
 ! 2.确定递推公式
 ! dp[i] += dp[以j为头结点左子树节点数量] * dp[以j为头结点右子树节点数量]，
 * j是头结点，从1遍历到i为止。
 * 所以递推公式：dp[i] += dp[j - 1] * dp[i - j]; ，
 * j-1 为j为头结点左子树节点数量，i-j 为以j为头结点右子树节点数量
 * 
 * 3.dp数组如何初始化
 * 初始化，只需要初始化dp[0]就可以了，推导的基础，都是dp[0]。
 * dp[0] = 1
 *
 * 4.确定遍历顺序
 * 首先一定是遍历节点数，从递归公式：dp[i] += dp[j - 1] * dp[i - j]可以看出，
 * 节点数为i的状态是依靠 i之前节点数的状态。
 * 那么遍历i里面每一个数作为头结点的状态，用j来遍历。
 * 
 * 5.举例推导dp数组
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};
// @lc code=end

