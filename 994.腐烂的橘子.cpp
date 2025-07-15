/*
 * @lc app=leetcode.cn id=994 lang=cpp
 * 图论
 ! [994] 腐烂的橘子
 */

// @lc code=start
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

/*
 * 别人的题解
 * 思路还是多源广度优先搜索，但代码比官方题解更容易理解
*/
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int num_r = grid.size();
        int num_c = grid[0].size();
        queue<pair<int, int>> Q;

        int cnt_good = 0;       //* 表示新鲜橙子的数量
        for (int row = 0; row < num_r; row++) {
            for (int col = 0; col < num_c; col++) {
                if (grid[row][col] == 1) {
                    cnt_good++;
                }
                else if (grid[row][col] == 2) {
                    Q.push(pair<int, int>{row, col});
                }
            }
        }

        int round = 0;          //* 表示腐烂的轮数，或者说分钟数
        while (!Q.empty() && cnt_good > 0) {    //! 注意这里的判断条件
            round++;
            //* 只遍历这一轮开始时就有的腐烂橙子，后面加进来的留到下一轮遍历
            int n = Q.size();
            for (int i = 0; i < n; i++) {
                int row = Q.front().first;
                int col = Q.front().second;
                Q.pop();
                if (row - 1 >= 0 && grid[row-1][col] == 1) {
                    cnt_good--;
                    grid[row-1][col] = 2;
                    Q.push(pair<int, int>{row - 1, col});
                }
                if (row + 1 < num_r && grid[row+1][col] == 1) {
                    cnt_good--;
                    grid[row+1][col] = 2;
                    Q.push(pair<int, int>{row + 1, col});
                }
                if (col - 1 >= 0 && grid[row][col-1] == 1) {
                    cnt_good--;
                    grid[row][col-1] = 2;
                    Q.push(pair<int, int>{row, col - 1});
                }
                if (col + 1 < num_c && grid[row][col+1] == 1) {
                    cnt_good--;
                    grid[row][col+1] = 2;
                    Q.push(pair<int, int>{row, col + 1});
                }
            }
        }

        if (cnt_good > 0) return -1;
        else return round;
    }
};

//* 官方题解，多源广度优先搜索
class Solution {
    int cnt;
    int dis[10][10];
    int dir_x[4] = {0, 1, 0, -1};
    int dir_y[4] = {1, 0, -1, 0};
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> Q;
        memset(dis, -1, sizeof(dis));
        cnt = 0;
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    Q.emplace(i, j);
                    dis[i][j] = 0;
                }
                else if (grid[i][j] == 1) {
                    cnt += 1;
                }
            }
        }
        while (!Q.empty()){
            int r = Q.front().first;
            int c = Q.front().second;
            Q.pop();
            for (int i = 0; i < 4; ++i) {
                int tx = r + dir_x[i];
                int ty = c + dir_y[i];
                if (tx < 0|| tx >= m || ty < 0|| ty >= n || ~dis[tx][ty] || !(grid[tx][ty] == 1)) {
                    continue;
                }
                dis[tx][ty] = dis[r][c] + 1;
                Q.emplace(pair<int, int>(tx, ty));
                cnt -= 1;
                ans = dis[tx][ty];
                if (!cnt) {
                    break;
                }
            }
        }
        return cnt ? -1 : ans;
    }
};

/*
 * 我的解法
 * 用当前grid推下一分钟grid的情况，然后将grid更新。
 * 也是多源广度优先搜索，但没有记录腐烂橙子的位置，而是遍历矩阵找腐烂橙子，
 * 更麻烦，而且无法区分腐烂橙子的层数。
*/
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int num_r = grid.size();
        if (num_r == 0) return 0;
        int num_c = grid[0].size();
        if (num_r == 0) return 0;

        vector<vector<int>> next_grid(num_r, vector<int>(num_c, 0));
        int cnt_good = 0;
        int cnt_bad = 0;

        for (int row = 0; row < num_r; row++) {
            for (int col = 0; col < num_c; col++) {
                if (grid[row][col] == 1) {
                    cnt_good++;
                    next_grid[row][col] = 1;
                }
                else if (grid[row][col] == 2) {
                    cnt_bad++;
                    next_grid[row][col] = 2;
                }
            }
        }

        if (cnt_good == 0) return 0;
        if (cnt_bad == 0) return -1;

        bool change = true;
        int time = 0;
        //* 如果没有剩余的新鲜橙子或者新增的腐烂橙子，退出循环
        while (cnt_good !=0 && change) {
            change = false;
            time++;

            for (int row = 0; row < num_r; row++) {
                for (int col = 0; col < num_c; col++) {
                    if (grid[row][col] == 2) {
                        if (row - 1 >= 0 && next_grid[row-1][col] == 1) {
                            cnt_good--;
                            change = true;
                            next_grid[row-1][col] = 2;
                        }
                        if (row + 1 < num_r && next_grid[row+1][col] == 1) {
                            cnt_good--;
                            change = true;
                            next_grid[row+1][col] = 2;
                        }
                        if (col - 1 >= 0 && next_grid[row][col-1] == 1) {
                            cnt_good--;
                            change = true;
                            next_grid[row][col-1] = 2;
                        }
                        if (col + 1 < num_c && next_grid[row][col+1] == 1) {
                            cnt_good--;
                            change = true;
                            next_grid[row][col+1] = 2;
                        }
                    }
                }
            }
            grid = next_grid;
        }

        if (cnt_good != 0) return -1;
        return time;
    }
};
// @lc code=end

