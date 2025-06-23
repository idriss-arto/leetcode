/*
 * @lc app=leetcode.cn id=152 lang=cpp
 * 动态规划
 * [152] 乘积最大子数组
 */

/*
 * 不能只维护最大值，因为可能有两个负数
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
            dpMax[i] = max({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            dpMin[i] = min({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            result = max(result, dpMax[i]);
        }

        return result;
    }
};
// @lc code=end

