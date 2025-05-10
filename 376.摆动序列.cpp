/*
 * @lc app=leetcode.cn id=376 lang=cpp
 * 贪心或动态规划
 * [376] 摆动序列
 */

/*
 * 两个思路，贪心或动态规划
 *
 * 贪心：
 * 找每一个波峰和每一个波谷
 * 需要考虑的特殊情况：
 * 情况一：上下坡中有平坡
 * 情况二：数组首尾两端
 * 情况三：单调坡中有平坡
 * 
 * 动态规划：
 * 对于数组中的某个元素，如果只考虑数组头到它，
 * 它要么是作为山峰（即 nums[i] > nums[j]），要么是作为山谷（即 nums[i] < nums[j]），其中0 < j < i
 * 设 dp 状态dp[i][0]，表示考虑到下标i，下标i作为山峰的摆动子序列的最长长度
 * 设 dp 状态dp[i][1]，表示考虑到下标i，下标i作为山谷的摆动子序列的最长长度
*/

// @lc code=start
#include <vector>
#include <climits>
#include <string.h>
using namespace std;

/*
 * Carl贪心
 * 思路，找波峰和波谷
 * 需要考虑的特殊情况：
 * 情况一：上下坡中有平坡
 * 情况二：数组首尾两端
 * 情况三：单调坡中有平坡
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
*/
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0;    //* 当前一对差值
        int preDiff = 0;    //* 前一对差值
        int result = 1;     //* 记录峰值个数，序列默认序列最右边有一个峰值
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            //* 出现峰值
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff;      //! 注意这里，只在摆动变化的时候更新prediff
                                        //* 如果这一行放在外面，则会导致单调坡度中出现平坡时会出现误判
            }
        }
        return result;
    }
};

//* 我的贪心
class Solution {
public:
    /*
     * 我的错误代码，
     * 思路是用一个flag来判断前一个趋势变化的点是波峰还是波谷
     * 但是对连续上坡后一个小下坡没处理好
     * 例如[1,2,4,3,4,3,4,3],我的代码只能找到[1,2]
     * 错误原因是遇见连续上坡时，应该取波峰而不是第一个遇见的值来判断有没有改变趋势
    */
    int myWiggleMaxLengthV1(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int left = 0;
        int right = 1;
        int flag = 0;
        while (flag == 0 && right < nums.size()) {
            if (nums[right] > nums[left]) flag = 1;
            else if (nums[right] < nums[left]) flag = -1;
            else right++;
        }

        if (right == nums.size()) return 1;     //* 数组中只有一种值，如[1,1,1,1,1,1]

        int result = 2;
        left = right;
        right++;
        while (right < nums.size()) {
            if (flag == 1) {
                if (nums[right] >= nums[left]) right++;
                else {
                    left = right;
                    flag = -1;
                    result++;
                    right++;
                }
            }
            else {
                if (nums[right] <= nums[left]) right++;
                else {
                    left = right;
                    flag = 1;
                    result++;
                    right++;
                }
            }
        }
        return result;
    }

    //* 改良后的我的代码，对连续上坡，取峰顶而不是第一个遇见的值（下坡同理）
    //* 例如[1,2,4,3,4,3,4,3]，改良前我的代码只能找到[1,2]，改良后能看到[1,4,...]
    int myWiggleMaxLengthV2(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int left = 0;
        int right = 1;
        int flag = 0;
        while (flag == 0 && right < nums.size()) {
            if (nums[right] > nums[left]) flag = 1;
            else if (nums[right] < nums[left]) flag = -1;
            else right++;
        }

        if (right == nums.size()) return 1;     //* 数组中只有一种值，如[1,1,1,1,1,1]

        int result = 2;
        left = right;
        right++;
        while (right < nums.size()) {
            if (flag == 1) {
                if (nums[right] == nums[left]) right++;
                else {
                    left = right;
                    right++;
                    if (nums[right] < nums[left]) {
                        flag = -1;
                        result++;
                    }
                }
            }
            else {
                if (nums[right] == nums[left]) right++;
                else {
                    left = right;
                    right++;
                    if (nums[right] > nums[left]) {
                        flag = 1;
                        result++;
                    }
                }
            }
        }
        return result;
    }
};

/*
 * Carl动态规划
 * 思路：
 * 对于数组中的某个元素，如果只考虑数组头到它，
 * 它要么是作为山峰（即 nums[i] > nums[j]），要么是作为山谷（即 nums[i] < nums[j]），其中0 < j < i
 *
 * 设 dp 状态dp[i][0]，表示考虑到下标i，下标i作为山峰的摆动子序列的最长长度
 * 设 dp 状态dp[i][1]，表示考虑到下标i，下标i作为山谷的摆动子序列的最长长度
 *
 * 则转移方程为：
 * dp[i][0] = max(dp[i][0], dp[j][1] + 1)，
 * 其中0 <= j < i且nums[j] < nums[i]，表示将 nums[i]接到前面某个山谷后面，作为山峰。
 * dp[i][1] = max(dp[i][1], dp[j][0] + 1)，
 * 其中0 <= j < i且nums[j] > nums[i]，表示将 nums[i]接到前面某个山峰后面，作为山谷。
 *
 * 初始状态：
 * 由于一个数可以接到前面的某个数后面，也可以以自身为子序列的起点，所以初始状态为：dp[0][0] = dp[0][1] = 1。
 * 
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(n)
*/
class Solution {
public:
    int dp[1005][2];
    int wiggleMaxLength(vector<int>& nums) {
        memset(dp, 0, sizeof dp);
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            dp[i][0] = dp[i][1] = 1;

            //* 考虑作为波谷
            for (int j = 0; j < i; ++j) {
                if (nums[j] > nums[i]) dp[i][1] = max(dp[i][1], dp[j][0] + 1);
            }

            //* 考虑作为波峰
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            }
        }
        return max(dp[nums.size() - 1][0], dp[nums.size() - 1][1]);
    }
};
// @lc code=end

