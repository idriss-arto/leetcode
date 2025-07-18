/*
 * @lc app=leetcode.cn id=46 lang=cpp
 * 回溯(排列)
 * [46] 全排列
 */
/*
 * 排列问题的不同：
 * 每层都是从0开始搜索而不是startIndex
 * 需要used数组记录path里都放了哪些元素了(树枝去重)
 * 
 * 因为没有index了，每次进入下一层都是从0开始遍历，
 * 因为给定数组不含重复数字，所以不用进行树层去重，
 * 只需使用used数组记录元素使用情况进行树枝去重。
*/
// @lc code=start
#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;

    void backtracking(const vector<int>& nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            //* 当前树枝已经用过此元素了则跳过
            if (used[i]) {
                continue;
            }
            used[i] = true;      //* 记录这个元素在本枝用过了，本枝后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums);
            used[i] = false;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        //* 在类的成员变量中声明，再在方法函数中重新定义大小。
        //* 避免每次回溯递归时传参
        used.resize(nums.size(), false);
        backtracking(nums);
        return result;
    }
};
// @lc code=end

