/*
 * @lc app=leetcode.cn id=37 lang=cpp
 * 回溯，位运算
 * [37] 解数独
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
private:
    bool isOK(vector<vector<char>>& board, int row, int column) {
        char now = board[row][column];
        //* 检查同一行和同一列
        for (int i = 0; i < 9; i++) {
            if (i != column && board[row][i] == now) return false;
        }
        for (int i = 0; i < 9; i++) {
            if (i != row && board[i][column] == now) return false;
        }

        int offsetX = row / 3;
        int offsetY = column / 3;
        for (int i = 0 + 3 * offsetX; i < 3 + 3 * offsetX; i++) {
            for (int j = 0 + 3 * offsetY; j < 3 + 3 * offsetY; j++) {
                if (i == row && j == column) continue;
                if (board[i][j] == now) return false;
            }
        }

        return true;
    }

    bool backtracking(vector<vector<char>>& board, int row, int column) {
        if (row == 9) return true;
        if (board[row][column] != '.') {
            if (column == 8) {
                if (backtracking(board, row + 1, 0)) return true;
            }
            else {
                if (backtracking(board, row, column + 1)) return true;
            }
        }
        else {
            for (int i = 1; i <= 9; i++) {
                board[row][column] = i + '0';
                if (isOK(board, row, column)) {
                    if (column == 8) {
                        if (backtracking(board, row + 1, 0)) return true;
                    }
                    else {
                        if (backtracking(board, row, column + 1)) return true;
                    }
                }
                board[row][column] = '.';
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board, 0, 0);
    }
};
/*
 * 题解写法，二维遍历，我是把二维拼成一个一维
class Solution {
private:
bool backtracking(vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); i++) {        // 遍历行
        for (int j = 0; j < board[0].size(); j++) { // 遍历列
            if (board[i][j] == '.') {
                for (char k = '1'; k <= '9'; k++) {     // (i, j) 这个位置放k是否合适
                    if (isValid(i, j, k, board)) {
                        board[i][j] = k;                // 放置k
                        if (backtracking(board)) return true; // 如果找到合适一组立刻返回
                        board[i][j] = '.';              // 回溯，撤销k
                    }
                }
                return false;  // 9个数都试完了，都不行，那么就返回false
            }
        }
    }
    return true; // 遍历完没有返回false，说明找到了合适棋盘位置了
}
bool isValid(int row, int col, char val, vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) { // 判断行里是否重复
        if (board[row][i] == val) {
            return false;
        }
    }
    for (int j = 0; j < 9; j++) { // 判断列里是否重复
        if (board[j][col] == val) {
            return false;
        }
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == val ) {
                return false;
            }
        }
    }
    return true;
}
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};
*/
/*
 * 官方题解，位运算+剪枝
class Solution {
private:
    //储存每一行存在的数字 
    int line[9];
    //储存 每一列存在的数字
    int column[9];
    //储存每一个 3*3宫存在的数字 
    int block[3][3];
    //这个布尔变量用来判断是否填完所有空格
    bool valid;
    //这个vector用来记录所有空格的位置，整数数组第一个位置为行的位置 ，第二个位置为列的位置
    vector<pair<int, int>> spaces;

public:
    void flip(int i, int j, int digit) {
        //^代表异或，只有1个1的时候才为1。比如0011^1001=1010
        //<<代表左移，比如 1<<2=4被加入到下面的三个数组中，
        //在二进制4为100，意味着3这个数字被占用了
        line[i] ^= (1 << digit);
        column[j] ^= (1 << digit);
        block[i / 3][j / 3] ^= (1 << digit);
    }

    void dfs(vector<vector<char>>& board, int pos) {
        //如果spaces被遍历完了，说明我们填完了空格，将valid改为true，通过return结束这个函数
        if (pos == spaces.size()) {
            valid = true;
            return;
        }
        
        //获取第一个空格的位置 
        auto [i, j] = spaces[pos];
        //|为or，通过3个或运算我们可以得到一个9位的二进制数字，
        //从右到左分别代表1-9这个9个数是否可以填入该空格，
        //通过~运算（取反），我们用1表示该数字是一个可填入的选项，
        //0x1ff为十六进制 ，等同于111111111）
        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1)) {
            //这个操作只保留最低位的1
            int digitMask = mask & (-mask);
            //最低位的1后面的位数也就是最低位的1在第几位上
            int digit = __builtin_ctz(digitMask);
            //更新行，列，宫
            flip(i, j, digit);
            //把该数填入板中
            board[i][j] = digit + '0' + 1;
            //继续搜索 
            dfs(board, pos + 1);
            //撤回操作（原理是flip中的~运算）
            flip(i, j, digit);
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        //初始化数组
        memset(line, 0, sizeof(line));
        memset(column, 0, sizeof(column));
        memset(block, 0, sizeof(block));
        valid = false;

        //遍历所有位置
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                //不为空则把该数字分别纳入对应的行，列，3*3宫中
                    int digit = board[i][j] - '0' - 1;
                    flip(i, j, digit);
                }
            }
        }

        //如果一个空白格只有唯一的数可以填入，
        //也就是其对应的 b 值和 b−1 进行按位与运算后得到 0（即 b 中只有一个二进制位为 1）。
        //此时，我们就可以确定这个空白格填入的数，而不用等到递归时再去处理它。
        while (true) {
            int modified = false;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] == '.') {
                    //|为or，通过3个或运算我们可以得到一个9位的二进制数字，
                    //从右到左分别代表1-9这个9个数是否可以填入该空格，
                    //通过~运算（取反），我们用1表示该数字是一个可填入的选项，
                    //0x1ff为十六进制 ，等同于111111111）
                        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
                        //mask & (mask - 1)把mask最低位的1变为0，如果这个值为0说明当前空只有一个值可以填
                        if (!(mask & (mask - 1))) {
                            //最低位的1后面的位数也就是最低位的1在第几位上
                            int digit = __builtin_ctz(mask);
                            //更新行，列，宫
                            flip(i, j, digit);
                            //把该数填入板中
                            board[i][j] = digit + '0' + 1;
                            modified = true;
                        }
                    }
                }
            }
            if (!modified) {
                break;
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                //如果位置为空，我们把该位置加入spaces中
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
            }
        }

        //开始搜索
        dfs(board, 0);
    }
};
*/
// @lc code=end