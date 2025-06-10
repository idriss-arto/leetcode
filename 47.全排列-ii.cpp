/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * 回溯(排列)
 ! [47] 全排列 II
 */

/*
 * 排列问题的不同：
 * 每层都是从0开始搜索而不是startIndex
 * 需要used数组记录path里都放了哪些元素了(树枝去重)
 * 
 * 因为没有index了，每次进入下一层都是从0开始遍历，
 * 同时同一元素（注意不是同一数字）在一个全排列中不会被多次使用，
 * 所以需要使用used数组记录元素使用情况进行树枝去重。
 * 
 * 同时，因为数组有重复元素，又要求求的全排列没有重复的，所以要树层去重
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
            used[i] = 0;            //* 准备进入同层下一个节点了，必须有这步回溯，不然每个元素在树中只能用一次，最后全排列只有一个
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

