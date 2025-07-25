/*
 * @lc app=leetcode.cn id=300 lang=cpp
 * 动态规划（递增序列）
 ! [300] 最长递增子序列
 */

/*
 * 思路一：
 * dp[i]表示nums[i]作为递增子序列最后一个元素时，递增子序列的最大长度
 * 则对j从0到i-1，执行if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
 * 注意，计算dp[i]时，nums[i]一定在递增子序列中，
 ! 所以dp.back()不是所求值，dp数组中的最大值才是
 * 
 ! dp[i]必须表示 “以nums[i]结尾的最长递增子序列” ，
 * 因为我们在做递增比较的时候，如果比较 nums[j] 和 nums[i] 的大小，
 * 那么两个递增子序列一定分别以 nums[j] 为结尾 和 nums[i] 为结尾，
 * 要不然这个比较就没有意义了
 * 时间复杂度：O(n^2)。空间复杂度O(N)
 * 
 * 
 * 思路二：贪心+二分查找
 * 通过维护一个tails数组，
 * 对输入数组nums中的每个元素，
 * 利用二分查找在tails中找到合适位置进行更新，
 * tails数组的有效长度即为原数组nums最长递增子序列的长度。
 * 时间复杂度：O(N*logN)。空间复杂度O(N)
*/

// @lc code=start
#include <vector>
using namespace std;

/*
 * 我的动态规划
 * 思路：dp[i]表示nums[i]作为递增子序列最后一个元素时，递增子序列的最大长度
 * 则对j从0到i-1，执行if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
 * 时间复杂度O（N^2）
 * 
 * 注意，计算dp[i]时，nums[i]一定在递增子序列中，
 ! 所以dp.back()不是所求值，dp数组中的最大值才是
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int maxLen = 1;         //* 不能初始化为小于1的数，否则数组大小为1时会出错

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;

    }
};

/*
 * 题解
 * 贪心+二分查找，思路：
 * 通过维护一个tails数组，
 * 对输入数组nums中的每个元素，
 * 利用二分查找在tails中找到合适位置（第一个大于自己的下标）进行更新，
 * tails数组的有效长度即为原数组nums最长递增子序列的长度。
 * 时间复杂度O（N * logN）
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tail;
        tail.push_back(nums[0]);
        for (const int& num : nums) {
            //! 如果当前数字大于tail数组尾部，则直接插入尾部
            if (num > tail.back()) {
                tail.push_back(num);
            }
            //! 否则，在tail数组中找到第一个大于等于这个数字的位置
            else {
                int left = 0;
                int right = tail.size() - 1;
                int mid;
                //! 想清楚二分查找要找啥，这里是找第一个大于等于nums[i]的位置
                while (left <= right) {
                    mid = left + (right - left) / 2;
                    if (tail[mid] < num) {
                        left = mid + 1;
                    }
                    else {          //* tails[middle] >= nums[i]
                        right = mid - 1;
                    }
                }
                tail[left] = num;
            }
        }
        return tail.size();
    }
};
// @lc code=end

