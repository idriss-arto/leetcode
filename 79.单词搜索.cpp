/*
 * @lc app=leetcode.cn id=79 lang=cpp
 * 回溯
 * [79] 单词搜索
 */

// @lc code=start
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
private:
    int m, n;
    vector<vector<bool>> used;
    vector<vector<int>> f{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    //* 判断board[row][col]是否为word[index]
    bool backtracking(vector<vector<char>>& board, string& word, int row, int col, int index) {
        if (board[row][col] != word[index]) {
            return false;
        }

        if (index == word.size() - 1) {
            return true;
        }

        used[row][col] = true;
        int next_row;
        int next_col;

        for (int i = 0; i < 4; i++) {
            next_row = row + f[i][0];
            next_col = col + f[i][1];
            if (next_row < 0 || next_row >= m || next_col < 0 || next_col >= n || used[next_row][next_col]) {
                continue;
            }
            if (backtracking(board, word, next_row, next_col, index+1)) {
                return true;
            }
        }

        //* 回溯
        used[row][col] = false;

        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();

        //* 根据输入的board大小重新定义used数组大小
        used.resize(m, vector<bool>(n, false));
        
        //* 遍历board每个位置尝试作为word的开始 
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtracking(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/*
 * 灵茶的优化代码
 * 优化一：
 * 如果 word 的某个字母的出现次数，比 board 中的这个字母的出现次数还要多，可以直接返回 false。
 * 
 * 优化二：
 * 设 word 的第一个字母在 board 中出现了 x 次，word 的最后一个字母在 board 中出现了 y 次。
 * 如果 y<x，我们可以把 word 反转，相当于从 word 的最后一个字母开始搜索，
 * 这样更容易在一开始就满足 board[i][j] != word[k]，不会往下递归，递归的总次数更少。
*/
class Solution {
private:
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    bool exist(vector<vector<char>>& board, string word) {
        unordered_map<char, int> cnt;
        for (auto& row : board) {
            for (char c : row) {
                cnt[c]++;
            }
        }

        //* 优化一
        unordered_map<char, int> word_cnt;
        for (char c : word) {
            if (++word_cnt[c] > cnt[c]) {
                return false;
            }
        }

        //* 优化二
        if (cnt[word.back()] < cnt[word[0]]) {
            word.reserve();
        }

        int m = board.size(), n = board[0].size();

        //* 判断board[i][j]是否为word[k]
        function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> bool {
            if (board[i][j] != word[k]) {   //* 匹配失败
                return false;
            }
            if (k + 1 == word.length()) {   //* 匹配成功！
                return true;
            }
            board[i][j] = 0;                //* 标记访问过
            for (auto& [dx, dy] : DIRS) {
                int x = i + dx, y = j + dy; //* 相邻格子
                if (0 <= x && x < m && 0 <= y && y < n && dfs(x, y, k + 1)) {
                    return true;            //* 搜到了！
                }
            }
            board[i][j] = word[k];          //* 恢复现场
            return false;                   //* 没搜到
        };

        //* 遍历board每个位置尝试作为word的开始
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(i, j, 0)) {
                    return true;            //* 搜到了！
                }
            }
        }
        return false;                       //* 没搜到
    }
};

// @lc code=end

