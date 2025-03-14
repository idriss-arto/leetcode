/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */

// @lc code=start
#include <vector>
#include <string>
using namespace std;
class Solution {
private:
    vector<vector<string>> results;
    vector<string> result;

    bool isOKPlace(int row, int column, int n) {
        for (int i = 0; i < n; i++) {
            if (result[row][i] == 'Q' || result[i][column] == 'Q') return false;
        }
        //* 右下
        for (int i = 0; ; i++) {
            if ((row + i >= n) || (column + i >= n)) break;
            if (result[row + i][column + i] == 'Q') return false;
        }
        //* 左上
        for (int i = 0; ; i++) {
            if ((row - i < 0) || (column - i < 0)) break;
            if (result[row - i][column - i] == 'Q') return false;
        }
        //* 左下
        for (int i = 0; ; i++) {
            if ((row + i >= n) || (column - i < 0)) break;
            if (result[row + i][column - i] == 'Q') return false;
        }
        //* 右上
        for (int i = 0; ; i++) {
            if ((row - i < 0) || (column + i >= n)) break;
            if (result[row + i][column - i] == 'Q') return false;
        }

        return true;
    }

    void backtracking(int row, int n) {
        if (row == n) {
            results.push_back(result);
            return ;
        }
        for (int i = 0; i < n; i++) {
            if (isOKPlace(row, i, n)) {
                result[row][i] = 'Q';
                backtracking(row + 1, n);
                result[row][i] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        string s(n, '.');
        for (int i = 0; i < n; i++) {
            result.push_back(s);
        }
        backtracking(0, n);
        return results;
    }
};
// @lc code=end

