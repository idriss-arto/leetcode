/*
 * @lc app=leetcode.cn id=376 lang=cpp
 * 贪心或动态规划
 * [376] 摆动序列
 */

// @lc code=start
#include <vector>
#include <climits>
#include <string.h>
using namespace std;
//* 贪心
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0;    //* 当前一对差值
        int preDiff = 0;    //* 前一对差值
        int result = 1;     //* 记录峰值个数，序列默认序列最右边有一个峰值
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            // 出现峰值
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff;      //! 注意这里，只在摆动变化的时候更新prediff
            }
        }
        return result;
    }

    //* 我的错误代码，对连续上坡后一个小下坡没处理好
    //* 例如[1,2,4,3,4,3,4,3],我的代码只能找到[1,2]
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

//* 动态规划
class Solution {
public:
    int dp[1005][2];
    int wiggleMaxLength(vector<int>& nums) {
        memset(dp, 0, sizeof dp);
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            dp[i][0] = dp[i][1] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] > nums[i]) dp[i][1] = max(dp[i][1], dp[j][0] + 1);
            }
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            }
        }
        return max(dp[nums.size() - 1][0], dp[nums.size() - 1][1]);
    }
};
// @lc code=end

