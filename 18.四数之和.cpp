/*
 * @lc app=leetcode.cn id=18 lang=cpp
 * 双指针（一定要排序）
 ! [18] 四数之和
 */

/*
 * 思路：
 * 和三数之和一个思路
 * 因为只返回值，所以可以排序改变顺序便于操作
 * 两层for循环遍历第一个和第二个值，再在后面的区域里用双指针确定剩下的两个值
 * 需要注意去重（第一第二个值和后面双指针都需要去重）
 * 另，此题可剪枝
 *
 ! 注意：此题需注意数值越界，中间计算结果需要用long储存
*/

// @lc code=start
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++) {
            //* 剪枝处理
            if (nums[k] > target && nums[k] >= 0) {
                break; //* 这里使用break，统一通过最后的return返回
            }
            //* 对nums[k]去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                //* 2级剪枝处理
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }

                //* 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    //* nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if ((long) nums[k] + nums[i] + nums[left] + nums[right] > target) {
                        right--;
                    //* nums[k] + nums[i] + nums[left] + nums[right] < target 会溢出
                    } else if ((long) nums[k] + nums[i] + nums[left] + nums[right]  < target) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        //* 对nums[left]和nums[right]去重
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;

                        //* 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }

            }
        }
        return result;
    }
};
// @lc code=end

