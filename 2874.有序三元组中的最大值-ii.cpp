/*
 * @lc app=leetcode.cn id=2874 lang=cpp
 * 动态规划
 * [2874] 有序三元组中的最大值 II
 */

/*
 * 固定j，找[0, j-1)的最大值和[j+1, nums.size())的最大值
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        vector<int> leftMaxIndex(nums.size(), 0);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[leftMaxIndex[i-1]] > nums[i-1]) leftMaxIndex[i] = leftMaxIndex[i-1];
            else leftMaxIndex[i] = i-1;
        }

        vector<int> rightMaxIndex(nums.size(), nums.size()-1);
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[rightMaxIndex[i+1]] > nums[i+1]) rightMaxIndex[i] = rightMaxIndex[i+1];
            else rightMaxIndex[i] = i+1;
        }

        long long result = 0;
        for (int i = 1; i <= nums.size() - 2; i++) {
            long long tmp = (long long)(nums[leftMaxIndex[i]] - nums[i]) * nums[rightMaxIndex[i]];
            result = max(result, tmp);
        }

        return result;
    }
};
// @lc code=end

