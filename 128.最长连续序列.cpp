/*
 * @lc app=leetcode.cn id=128 lang=cpp
 * 哈希
 ! [128] 最长连续序列
 */

/*
 * 思路：
 * 先用unordered_set去重，
 * 然后对于num_set中的每个元素x，判断x-1是否在num_set中，
 * 如果在，说明以x开头的连续序列一定不是最长的（因为可以在这个序列前面加上x-1），
 * 如果不在，递归查找x+1,x+2,⋯是否存在，假设最长匹配到了x+y，那么以x开头的最长连续序列长度为y+1
*/

// @lc code=start
#include <vector>
#include <unordered_set>
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //* 这里直接传入数组的迭代器初始化unordered_set，不用一个个遍历
        unordered_set<int> num_set(nums.begin(), nums.end());

        int longestStreak = 0;

        //! 注意这里遍历的是num_set，而不是nums，因为num_set中放的是去重后的结果
        //* 如果遍历的是nums会超时
        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;           
    }
};
// @lc code=end

