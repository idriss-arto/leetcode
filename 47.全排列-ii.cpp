/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * 回溯(排列)
 * [47] 全排列 II
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<int> used;

    void backtracking(const vector<int>& nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if ((used[i]) == 1) continue;                                   //* 同枝去重
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;      //* 同层去重
            used[i] = 1;            //* 记录这个元素在本枝用过了，本枝后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums);
            used[i] = 0;            //* 准备进入同层下一个节点了
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        used.resize(nums.size(), 0);
        backtracking(nums);
        return result;
    }
};
// @lc code=end

