/*
 * @lc app=leetcode.cn id=560 lang=cpp
 * 前缀和 + 哈希表优化
 ! [560] 和为 K 的子数组
 */

// @lc code=start
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
 * 官方题解，思路：
 * 前缀和 + 哈希表优化
 * 在考虑以 i 结尾的和为 k 的连续子数组个数时，
 * 只要统计目前有多少个前缀和为 preSum[i]−k 的 preSum[j] （0 <= j < i）即可
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        //* map统计已出现的前缀和和出现次数
        unordered_map<int, int> mp;

        //! 关键步骤
        mp[0] = 1;

        int count = 0, preSum = 0;
        for (auto& x : nums) {
            preSum += x;
            //* 从map中寻找满足preSum[i]-preSum[j]==k的j有几个
            if (mp.find(preSum - k) != mp.end()) {
                count += mp[preSum - k];
            }
            mp[preSum]++;
        }
        
        return count;
    }
};

/*
 * 我的思路：前缀和
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> sum(nums.size() + 1, 0);
        sum[1] = nums[0];
        for (int i = 2; i <= nums.size(); i++) {
            sum[i] = sum[i-1] + nums[i - 1];
        }

        int result = 0;
        for (int i = 0; i <= nums.size(); i++) {
            for (int j = i + 1; j <= nums.size(); j++) {
                if ((sum[j] - sum[i]) == k) result++;
            }
        }

        return result;
    }
};
// @lc code=end

