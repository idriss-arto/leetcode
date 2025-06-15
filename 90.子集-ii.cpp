/*
 * @lc app=leetcode.cn id=90 lang=cpp
 * 回溯(子集)，树层去重
 ! [90] 子集 II
 */

/*
 * 此题集合中有重复的元素，要求子集中可以有重复的元素，但是不能有重复的子集。
 * 所以需要进行树层去重（树层去重和树枝去重区别可见40）
 * 
 * 树层去重思路：
 * 一：排序+startIndex判断是同一树枝还是同一树层
 * 二：排序+used数组判断是同一树枝还是同一树层
 * 三：排序+每层定义一个set记录哪些数用过
*/

// @lc code=start
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

//* startIndex判断进行树层去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int cnt, int startIndex) {
        if (cnt == 0) result.push_back(path);
        if (startIndex >= nums.size()) return;       //* 这行不加也可以
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > startIndex && nums[i] == nums[i - 1]) continue;  //* 树层去重
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

//* used数组判断进行树层去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int startIndex, vector<bool>& used) {
        result.push_back(path);
        for (int i = startIndex; i < nums.size(); i++) {
            //* used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
            //* used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            //* 而我们要对同一树层使用过的元素进行跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());     //* 去重需要排序
        backtracking(nums, 0, used);
        return result;
    }
};

//* set去重进行树层去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        unordered_set<int> uset;        //! 不能定义为全局变量，因为只记录本层
        for (int i = startIndex; i < nums.size(); i++) {
            if (uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end());     //* 去重需要排序
        backtracking(nums, 0);
        return result;
    }
};
// @lc code=end

