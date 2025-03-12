/*
 * @lc app=leetcode.cn id=90 lang=cpp
 * 回溯(子集)
 * [90] 子集 II
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int cnt, int index) {
        if (cnt == 0) result.push_back(path);
        if (index >= nums.size()) return;
        for (int i = index; i < nums.size(); i++) {
            if (i > index && nums[i] == nums[i - 1]) continue;  //* 树层去重
            path.push_back(nums[i]);
            backtracking(nums, cnt - 1, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());     //* 去重需要对数组排序
        result.push_back(nums);
        for (int i = 0; i <= nums.size() - 1; i++) {
            path.clear();
            backtracking(nums, i, 0);
        }
        return result;
    }
};
// @lc code=end

