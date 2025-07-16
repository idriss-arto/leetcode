/*
 * @lc app=leetcode.cn id=40 lang=cpp
 * 回溯（组合），剪枝，树层去重与树枝去重的区别
 ! [40] 组合总和 II
 */

/*
 * 这里candidates是有重复元素的，所以需要考虑去重
 * 因为每个数字只能选取一次，所以递归调用回溯函数时，startIndex为i+1
 * 
 * 因为一个组合里，可以有重复元素，但是不能有重复的组合，所以这是树层去重，
 * 因为同一树枝（递归的过程）是一个组合里的元素，同一树层（for循环）是不同的组合
 * 
 * 树层去重思路：
 * 一：排序+startIndex判断是同一树枝还是同一树层
 * 二：排序+used数组判断是同一树枝还是同一树层
 * 三：排序+每层定义一个set记录哪些数用过
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
    int sum = 0;
    vector<bool> used;

    void backtracking(vector<int>& candidates, int target, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size(); i++) {
            //* 去重
            if (sum + candidates[i] > target) break;
            
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
             * 还有一种写法见90
            */

            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target, i + 1);
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        used.resize(candidates.size());
        path.clear();
        result.clear();
        //* 首先把candidates给排序，让其相同的元素都挨在一起，便于后续去重和剪枝
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0);
        return result;
    }
};
// @lc code=end

