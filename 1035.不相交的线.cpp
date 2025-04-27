/*
 * @lc app=leetcode.cn id=1035 lang=cpp
 * 动态规划（不连续子序列）
 * [1035] 不相交的线
 */

/*
 * 思路：
 * 只要能想到把这题转换成求最长公共子序列，就好做了
 * 绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，只要 nums1[i] == nums2[j]，且直线不能相交！
 * 直线不能相交，这就是说明在字符串nums1中 找到一个与字符串nums2相同的子序列，
 * 且这个子序列在两个字符串中相对顺序一致，只要相对顺序不改变，连接相同数字的直线就不会相交。
 * 最长公共子序列详细思路见1143
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[nums1.size()][nums2.size()];
    }
};
// @lc code=end

