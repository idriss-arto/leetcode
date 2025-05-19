/*
 * @lc app=leetcode.cn id=509 lang=cpp
 * 动态规划
 * [509] 斐波那契数
 */

/*
 * 动态规划五步走：
 * 1.确定dp数组（dp table）以及下标的含义
 * 2.确定递推公式
 * 3.dp数组如何初始化
 * 4.确定遍历顺序
 * 5.举例推导dp数组
*/

// @lc code=start
#include <vector>
using namespace std;

//* 普通版
class Solution {
public:
    int fib(int n) {
        if (n == 0 || n == 1) return n;
        vector<int> result(n + 1, 0);
        result[1] = 1;
        for (int i = 2; i < result.size(); i++) {
            result[i] = result[i-1] + result[i-2];
        }
        return result[n];
    }
};

//* 空间复杂度优化版
class Solution {
public:
    int fib(int N) {
        if (N <= 1) return N;
        int dp[2];
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= N; i++) {
            int sum = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = sum;
        }
        return dp[1];
    }
};
// @lc code=end

