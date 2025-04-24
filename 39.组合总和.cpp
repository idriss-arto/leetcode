/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * 回溯（组合），剪枝
 * [39] 组合总和
 */

/*
 * 这里candidates是无重复元素的，所以不用考虑去重
 * 因为每个数字可以重复选取，所以递归调用回溯函数时，startIndex不是i+1而是i
 * 
 * 本题可剪枝，
 * 剪枝思路：
 * for循环中（同一层中），sum + candidates[i] > target 就终止遍历，
 * 因为candidates有经过排序，所以后面的元素只会更大，即对于j大于i，
 * sum + candidates[j] 也会大于 target
*/

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }

        //* 如果 sum + candidates[i] > target 就终止遍历
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i);       //* 不用i+1了，表示可以重复读取当前的数
            sum -= candidates[i];
            path.pop_back();

        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        sort(candidates.begin(), candidates.end());     //* 剪枝需要排序
        backtracking(candidates, target, 0, 0);
        return result;
    }
};
// @lc code=end

