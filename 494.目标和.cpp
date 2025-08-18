/*
 * @lc app=leetcode.cn id=494 lang=cpp
 * 动态规划
 ! [494] 目标和
 */

/*
 * 给定背包容量，装满背包有多少种方法
*/

/*
 * 我的思路：
 * 让dp[i][j]表示前i个数组成数字j的可能方式数
 * 则状态转移方程为：dp[i][j] = dp[i-1][j-nums[i]] + dp[i-1][j+nums[i]]
 * 问题：target范围为[-1000,1000]，所以得让dp[i][j]表示前i个数组成数字（j-1000）的可能方式数
 ? 理解难度低，但计算较为复杂
 * 
 * 题解思路：
 * 假设nums中数字全部取正时，和为sum
 * 为了取得target，可以将取正的数全部挪到左边，取负的数全部挪到右边
 * 即取正的数的和为left，取负的数的绝对值和为right
 * 则此时有left+right=sum，left-right=target
 * 则2*left = target+sum，其中target和sum是已知的，可以求出left
 ! 注意：target+sum为奇数时，left不为整数，即无解
 * 则原问题转换为求“取nums中的数（每一个数分为取和不取），使得和为left的取法计数”
*/
 
// @lc code=start
#include <vector>
#include <math.h>
using namespace std;

/*
 * 题解解法
 * 思路：
 * 假设nums中数字全部取正时，和为sum
 * 为了取得target，可以将取正的数全部挪到左边，取负的数全部挪到右边
 * 即取正的数的和为left，取负的数的绝对值和为right
 * 则此时有left+right=sum，left-right=target
 * 则2*left = target+sum，其中target和sum是已知的，可以求出left
 ! 注意：target+sum为奇数时，left不为整数，即无解
 * 则原问题转换为求“取nums中的数（每一个数分为取和不取），使得和为left的取法计数”
 *
 * dp[i][j]表示前i个数(从下标0到下标i-1)，有多少种取法使得和为j
*/
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) sum += nums[i];

        if (abs(target) > sum) return 0;        //* 此时没有方案
        if ((target + sum) % 2 == 1) return 0;  //! 此时没有方案

        int bagSize = (target + sum) / 2;
        
        vector<vector<int>> dp(nums.size()+1, vector<int>(bagSize + 1, 0));

        //* 初始化最左列，最左列其他数值在递推公式中就完成了赋值
        dp[0][0] = 1; 

        /*
         ! 根据前i个数中0的个数，前i个数组成0的方式也会不同
         * 但以下代码也可以不加上，结果是一样的，
         * 加上后，下面的遍历里j可以从1开始
        int numZero = 0;
        for (int i = 1; i <= nums.size(); i++) {
            if (nums[i-1] == 0) numZero++;
            dp[i][0] = (int) pow(2.0, numZero);
        }
        */
        

        //* 以下遍历顺序行列可以颠倒
        for (int i = 1; i <= nums.size(); i++) { 
            for (int j = 0; j <= bagSize; j++) {
                if (nums[i-1] > j) dp[i][j] = dp[i - 1][j]; 
                else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i-1]];
            }
        }
        return dp[nums.size()][bagSize];
    }
};

//* 题解解法，滚动数组版
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (const int& num : nums) {
            sum += num;
        }

        if (abs(sum) < abs(target)) return 0;
        if ((sum + target) % 2 != 0) return 0;

        int bagSize = (target + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp.back();
    }
};

/*
 * 我的解法
 * 思路：
 * 让dp[i][j]表示前i个数组成数字j的可能方式数
 * 则状态转移方程为：dp[i][j] = dp[i-1][j-nums[i]] + dp[i-1][j+nums[i]]
 * 问题：target范围为[-1000,1000]，所以让dp[i][j]表示前i个数组成数字（j-1000）的可能方式数
*/
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        /*
         * 因为target范围为[-1000,1000]，所以让dp[i][j]表示前i个数组成数字（j-1000）的可能方式数
         * 则状态转移方程为：dp[i][j] = dp[i-1][j-nums[i]] + dp[i-1][j+nums[i]]
        */
        vector<vector<int>> dp(nums.size(), vector<int>(2005, 0));
        
        //* 注意，这里不能写"=1"，因为nums[0]可能为0
        dp[0][1000+nums[0]] += 1;
        dp[0][1000-nums[0]] += 1;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= 2000; j++) {
                if (j - nums[i] >= 0) dp[i][j] += dp[i-1][j-nums[i]];
                if (j + nums[i] <= 2000) dp[i][j] += dp[i-1][j+nums[i]];
            }
        }
        return dp[nums.size() - 1][target + 1000];
    }
};
// @lc code=end

