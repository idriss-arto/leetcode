/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * 回溯，剪枝
 * [39] 组合总和
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;

    bool backtracking(vector<int>& candidates, int target, int index) {
        if (sum == target) {
            result.push_back(path);
            return true;                //* 已经取到目标值了，不用遍历后面相等或更大的值
        }
        if (sum > target) return true;  //* 剪枝
        for (int i = index; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            if (backtracking(candidates, target, i)) {      //! 剪枝判断
                sum -= candidates[i];
                path.pop_back();
                break;
            }
            else {
                sum -= candidates[i];
                path.pop_back();
            }
        }
        return false;
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());     //* 剪枝需要排序
        backtracking(candidates, target, 0);
        return result;
    }
};
// @lc code=end

