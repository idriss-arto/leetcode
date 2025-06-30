/*
 * @lc app=leetcode.cn id=152 lang=cpp
 * 动态规划
 * [152] 乘积最大子数组
 */

/*
 * 不能只维护最大值，因为可能有两个负数
 * 需要同时维护最大值，最小值
 * 计算当前位置的最大值时，需要使用到上一个位置的最大值和最小值以及当前位置的元素
 * 最小值同理
*/

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> dpMax(nums.size(), 0);
        vector<int> dpMin(nums.size(), 0);
        dpMax[0] = nums[0];
        dpMin[0] = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            //* 计算最大值时不能只用上一个位置的最大值，还要使用上一个位置的最小值
            //* 计算最小值时同理
            dpMax[i] = max({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            dpMin[i] = min({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            result = max(result, dpMax[i]);
        }

        return result;
    }
};
// @lc code=end

