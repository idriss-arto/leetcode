/*
 * @lc app=leetcode.cn id=491 lang=cpp
 * 回溯(子集)
 * [491] 非递减子序列
 */
//! 同层去重特殊情况，不能排序
// @lc code=start
#include <vector>
using namespace std;
class Solution {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex) {
            if (path.size() > 1) {
                result.push_back(path);
            }
            int used[201] = {0};            //* 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
                                            //! 不能定义为全局变量，因为只记录本层
            for (int i = startIndex; i < nums.size(); i++) {
                if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) {
                        continue;
                }
                used[nums[i] + 100] = 1;    //* 记录这个元素在本层用过了，本层后面不能再用了
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
        }
    public:
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
// @lc code=end

