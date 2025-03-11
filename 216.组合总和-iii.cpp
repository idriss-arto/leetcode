/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * 回溯，剪枝
 * [216] 组合总和 III
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;     //* 存放结果集
    vector<int> path;               //* 符合条件的结果
    int sum = 0;                    //* 当前路径的和
    void backtracking(int targetSum, int k, int startIndex) {
        if (sum > targetSum) {      //* 剪枝操作
            return; 
        }
        if (path.size() == k - 1 && startIndex <= targetSum - sum && targetSum - sum <= 9) {
            path.push_back(targetSum - sum);
            result.push_back(path);
            path.pop_back();
            return;
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { //* 剪枝
            sum += i;           //* 处理
            path.push_back(i);  //* 处理
            backtracking(targetSum, k, i + 1);  //* 注意i+1调整startIndex
            sum -= i;           //* 回溯
            path.pop_back();    //* 回溯
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear(); //* 可以不加
        path.clear();   //* 可以不加
        backtracking(n, k, 1);
        return result;
    }
};
// @lc code=end

