/*
 * @lc app=leetcode.cn id=53 lang=cpp
 * 贪心或动态规划
 * [53] 最大子数组和
 */

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
//* 贪心
class Solution {
public:
    //* 题解写法
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i];
            if (count > result) {       //* 取区间累计的最大值（相当于不断确定最大子序终止位置）
                result = count;
            }
            if (count <= 0) count = 0;  //* 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
        }
        return result;
    }

    //* 我的解法，虽然过了，但太麻烦，没体现贪心的好处
    int myMaxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int sum = 0;
        int now = 0;
        int index = 0;
        
        //* 先找到第一个正值
        for (; index < nums.size() && nums[index] <= 0; index++){           //! 不能写成nums[index] <= 0 && index < nums.size()，会越界！
            result = result > nums[index] ? result : nums[index];
        };

        //* 特殊情况处理：数组里全是负值
        if (index == nums.size()) return result;

        for (int i = index; i < nums.size(); i++) {
            if (nums[i] >= 0) {
                sum += nums[i];
                continue;
            }
            else {
                result = result > sum ? result : sum;
                now = 0;
                while (i < nums.size() && nums[i] < 0) {
                    now += nums[i];
                    i++;
                }
                if (i == nums.size()) {
                    break;
                }
                else {
                    if (sum + now >= 0) {
                        sum += nums[i] + now;
                        continue;
                    }
                    else {
                        sum = nums[i];
                    }
                }
            }
        }
        result = result > sum ? result : sum;
        return result;
    }
};
// @lc code=end

