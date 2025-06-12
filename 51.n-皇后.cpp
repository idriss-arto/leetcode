/*
 * @lc app=leetcode.cn id=51 lang=cpp
 * 回溯
 ! [51] N 皇后
 */

/*
 * 思路：
 * 按行遍历，找到能放的位置就进入下一行
 * 
 * 找能放的行有两个方法：
 * 一：遍历列和左上、右上即可（简单）
 ! 二：位运算（困难）
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
        //* 因为按行遍历，所以只检查列就可以了，而且右下和左下也不用检查
        // for (int i = 0; i < n; i++) {
        //     if (result[row][i] == 'Q' || result[i][column] == 'Q') return false;
        // }
        for (int i = 0; i < row; i++) {
            if (result[i][column] == 'Q') return false;
        }
        //* 右下
        // for (int i = 0; ; i++) {
        //     if ((row + i >= n) || (column + i >= n)) break;
        //     if (result[row + i][column + i] == 'Q') return false;
        // }
        //* 左上
        for (int i = 0; ; i++) {
            if ((row - i < 0) || (column - i < 0)) break;
            if (result[row - i][column - i] == 'Q') return false;
        }
        //* 左下
        // for (int i = 0; ; i++) {
        //     if ((row + i >= n) || (column - i < 0)) break;
        //     if (result[row + i][column - i] == 'Q') return false;
        // }
        //* 右上
        for (int i = 0; ; i++) {
            if ((row - i < 0) || (column + i >= n)) break;
            if (result[row - i][column + i] == 'Q') return false;
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

//* 官方题解
//* 用位运算记录之前的皇后位置并计算当前能放哪
class Solution {
private:
    vector<vector<string>> solutions;
    vector<int> queens;                 //* queens 记录皇后位置，queens[i] 为 j 说明第i行的皇后在第j列

    //* 当n个皇后的位置都确定后，用此函数生成一个答案棋盘
    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }

    //* 回溯函数
    void solve(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, int columns, int diagonals1, int diagonals2) {
        if (row == n) {
            auto board = generateBoard(queens, n);
            solutions.push_back(board);
        } else {
            //* 下一行处理后，availablePositions低n位表示目前行n列能不能放皇后，为1表示能放
            int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
            while (availablePositions != 0) {
                /*
                 ! x & (−x) 可以获得 x 的二进制表示中的最低位的 1 的位置。
                 ! x & (x−1) 可以将 x 的二进制表示中的最低位的 1 置成 0。
                */
                int position = availablePositions & (-availablePositions);
                availablePositions = availablePositions & (availablePositions - 1);
                //* 计算最低位 1 的位置，从右往左，第一个'1'之前的'0'的个数
                int column = __builtin_ctz(position);
                queens[row] = column;
                solve(solutions, queens, n, row + 1, columns | position, (diagonals1 | position) >> 1, (diagonals2 | position) << 1);
                queens[row] = -1;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        queens.resize(n, -1);
        solve(solutions, queens, n, 0, 0, 0, 0);
        return solutions;
    }
};
// @lc code=end

