/*
 * @lc app=leetcode.cn id=343 lang=cpp
 * 动态规划
 ! [343] 整数拆分
 */

/*
 * 思路：
 * 因为是将正整数 n 拆分为至少两个正整数的和，并使这些整数的乘积最大化。 
 * 令dp[i]表示正整数 i 能得到的最大乘积。
 * 显然，可以把 i 划分为 j 和 i-j 两个部分（1 <= j <= i/2）,
 * 而 j 和 i-j 两部分需不需要再拆分，就需要列举比较乘积
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int integerBreak(int n) {
        //* result[i] 为正整数 i 拆分后的结果的最大乘积
        vector<int> result(n+1);
        result[0] = 0;
        result[1] = 0;
        result[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j <= i / 2; j++) {
                result[i] = max(result[i], j * (i - j));
                result[i] = max(result[i], result[j] * (i - j));
                result[i] = max(result[i], j * result[i-j]);
                result[i] = max(result[i], result[j] * result[i-j]);
                /*
                 * 也可以把上面四行换成下面一行
                result[i] = max(result[i], max(j, result[j]) * max((i - j), result[i-j]));
                */
            }
            /*
             * 也可以这么写
             * 让 j 表示拆分出来的第一个整数
             * for (int j = 1; j <= i / 2; j++) {
             *     dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
             * }
            */
            
        }
        return result[n];
    }
};
// @lc code=end

