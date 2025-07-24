/*
 * @lc app=leetcode.cn id=279 lang=cpp
 * 动态规划（完全背包）
 ! [279] 完全平方数
 */

/*
 * 我的思路：
 * 将要拼凑的数 i 分为两部分，j 和 i-j ，
 * 然后遍历 j 从 1 到 i/2，使得dp[i] = min(dp[i], dp[i - j] + dp[j])
 * 最后超时
 * 
 * 题解思路：
 * 还是将要拼凑的数 i 分为两部分，j 和 i-j ，
 ! 但可以确定 j 应该是一个平方数，
 * 也就是可以把 i 分为 j*j 和 i-j*j 两部分。
 * 这样j需要遍历的范围大大减小。 
*/

// @lc code=start
#include <vector>
#include <math.h>
using namespace std;

//* 题解解法
//* 遍历j * j <= i，使得dp[i] = min(dp[i - j * j] + 1, dp[i]);即可
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, __INT_MAX__);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) {          //* 遍历背包
            for (int j = 1; j * j <= i; j++) {  //* 遍历物品
                dp[i] = min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};

//! 超时
//* 我的解法
//* 遍历所有j <= n / 2，使得dp[i] = min(dp[i], dp[i - j] + dp[j]);
class Solution {
//* dp[i]表示数字i由完全平方数组成所需的最少数字
public:
    int numSquares(int n) {
        vector<int> dp(n+1, __INT_MAX__);
        
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {                  //* 遍历背包
            int x = sqrt(i);
            if (x == i / x && i % x == 0) dp[i] = 1;    //* 自己就是平方数
            else {
                for (int j = 1; j <= n / 2; j++) {      //* 遍历物品
                    if (dp[j] != __INT_MAX__ && dp[i-j] != __INT_MAX__) {
                        dp[i] = min(dp[i], dp[i - j] + dp[j]);
                    }
                }
            }
        }

        return dp[n];
    }
};
// @lc code=end

