/*
 * @lc app=leetcode.cn id=718 lang=cpp
 * 动态规划（连续子序列）
 * [718] 最长重复子数组
 */

/*
 * 最长重复子数组即最长公共连续子序列
 * 
 * 题解动态规划
 * 思路：
 * dp[i][j] ：对于以下标i - 1为结尾的A，和以下标j - 1为结尾的B，最长重复子数组长度为dp[i][j]。 
 *（特别注意： “以下标i - 1为结尾的A” 标明一定是 以A[i-1]为结尾的字符串 ）
 * 状态转移方程和下一个思路一样
 * 这样写不用单独初始化
 ! 注意，由于dp[i][j]一定包含A[i-1]和B[j-1]，所以dp.back().back()不一定是最大值
 * 
 * 我的思路：
 * dp[i][j]表示以下标i为结尾的A，和以下标j为结尾的B，能满足的公共最长连续子序列。
 * （特别注意： “以下标i为结尾的A” 标明一定是 以nums1[i]为结尾的字符串 ）
 * if (nums1[i] == nums2[j]) dp[i][j] = dp[i-1][j-1] + 1;
 ! else dp[i][j] = 0; 
 * 注意，else情况下不是max(dp[i-1][j], dp[i][j-1])，因为这里要求连续序列
 * 需要初始化第一行和第一列 
*/

// @lc code=start
#include <vector>
using namespace std;

/*
 * Carl动态规划
 * 思路：
 * dp[i][j] ：以下标i - 1为结尾的A，和以下标j - 1为结尾的B，最长重复子数组长度为dp[i][j]。 
 *（特别注意： “以下标i - 1为结尾的A” 标明一定是 以A[i-1]为结尾的字符串 ）
 * 这样写不用单独初始化
*/
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp (nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                //! 注意这里是比较下标i-1和下标j-1
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }

                if (dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};

//* Cral动态规划（滚动数组版）
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<int> dp(vector<int>(B.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= A.size(); i++) {
            //* 注意这里是从后往前遍历，避免状态转移时用到错的值
            for (int j = B.size(); j > 0; j--) {
                if (A[i - 1] == B[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                } 
                else dp[j] = 0;                 //! 注意这里不相等的时候要有赋0的操作，和二维数组版不一样
                if (dp[j] > result) result = dp[j];
            }
        }
        return result;
    }
};

/* 
 * 我的思路：
 * dp[i][j]表示数组一包含nums1[i]（只考虑下标i之前）
 * 数组二包含nums2[j]的子序列（只考虑下标j之前），能满足的公共最长子数组
 * if (nums1[i] == nums2[j]) dp[i][j] = dp[i-1][j-1] + 1;
 * else dp[i][j] = 0; 
 * 需要初始化第一行和第一列
*/
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size(), vector<int>(nums2.size(), 0));
        
        int maxCnt = 0;

        //* 初始化第一行和第一列
        for (int i = 0; i < nums1.size(); i++) {
            if (nums1[i] == nums2[0]) {
                dp[i][0] = 1;
                maxCnt = 1;
            }
        }
        for (int j = 0; j < nums2.size(); j++) {
            if (nums1[0] == nums2[j]) {
                dp[0][j] = 1;
                maxCnt = 1;
            }
        }

        for (int i = 1; i < nums1.size(); i++) {
            for (int j = 1; j < nums2.size(); j++) {
                if (nums1[i] != nums2[j]) dp[i][j] = 0;
                else {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    maxCnt = max(maxCnt, dp[i][j]);
                }
            }
        }
        
        return maxCnt;
    }
};
// @lc code=end

