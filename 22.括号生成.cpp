/*
 * @lc app=leetcode.cn id=22 lang=cpp
 * 回溯
 * [22] 括号生成
 */

// @lc code=start
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    vector<string> result;
    string path = "";

    void backtracking(int left, int right, int n) {
        if (left == n && right == n) {
            result.push_back(path);
            return;
        }

        if (left < n) {
            path.push_back('(');
            backtracking(left+1, right, n);
            path.pop_back();
        }

        if (right < left) {
            path.push_back(')');
            backtracking(left, right+1, n);
            path.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        backtracking(0, 0, n);
        return result;
    }
};
// @lc code=end

