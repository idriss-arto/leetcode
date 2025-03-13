/*
 * @lc app=leetcode.cn id=40 lang=cpp
 * 回溯，剪枝，同层去重与同枝去重的区别
 * [40] 组合总和 II
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex, vector<bool> used) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            //* used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
            //* used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            //* 要对同一树层使用过的元素进行跳过
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
                continue;
            }

            /*
             * 同层去重也可以就用startIndex判断，就不用used数组
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }
             * 还有一种写法见491
            */

            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target, sum, i + 1, used);
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size(), false);
        path.clear();
        result.clear();
        //* 首先把给candidates排序，让其相同的元素都挨在一起。
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, used);
        return result;
    }
};
// @lc code=end

