/*
 * @lc app=leetcode.cn id=200 lang=cpp
 * 图论
 * [200] 岛屿数量
 */

// @lc code=start
#include <vector>
#include <queue>
using namespace std;

/*
 * 深度优先搜索
 * 将二维网格看成一个无向图，竖直或水平相邻的 1 之间有边相连。
 * 扫描整个二维网格。如果一个位置为 1，则以其为起始节点开始进行深度优先搜索。
 * 在深度优先搜索的过程中，每个搜索到的 1 都会被重新标记为 0。
 * 时间复杂度：O(MN)，空间复杂度O(MN)
*/
class Solution {
private:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int num_r = grid.size();
        int num_c = grid[0].size();

        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r-1][c] == '1') dfs(grid, r - 1, c);
        if (r + 1 < num_r && grid[r+1][c] == '1') dfs(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c-1] == '1') dfs(grid, r, c - 1);
        if (c + 1 < num_c && grid[r][c+1] == '1') dfs(grid, r, c + 1);
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int num_r = grid.size();
        if (!num_r) return 0;
        int num_c = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < num_r; ++r) {
            for (int c = 0; c < num_c; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    dfs(grid, r, c);
                }
            }
        }

        return num_islands;
    }
};

/*
 * 广度优先搜索
 * 将二维网格看成一个无向图，竖直或水平相邻的 1 之间有边相连。
 * 扫描整个二维网格。如果一个位置为 1，则将其加入队列，开始进行广度优先搜索。
 * 在广度优先搜索的过程中，每个搜索到的 1 都会被重新标记为 0。直到队列为空，搜索结束。
 * 时间复杂度：O(MN)，空间复杂度：O(min(M,N))
*/
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int num_r = grid.size();
        if (!num_r) return 0;
        int num_c = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < num_r; ++r) {
            for (int c = 0; c < num_c; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    while (!neighbors.empty()) {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        if (row - 1 >= 0 && grid[row-1][col] == '1') {
                            neighbors.push({row-1, col});
                            grid[row-1][col] = '0';
                        }
                        if (row + 1 < num_r && grid[row+1][col] == '1') {
                            neighbors.push({row+1, col});
                            grid[row+1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col-1] == '1') {
                            neighbors.push({row, col-1});
                            grid[row][col-1] = '0';
                        }
                        if (col + 1 < num_c && grid[row][col+1] == '1') {
                            neighbors.push({row, col+1});
                            grid[row][col+1] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};

/* 
 * 并查集
 * 扫描整个二维网格。如果一个位置为 1，则将其与相邻四个方向上的 1 在并查集中进行合并。
 * 最终岛屿的数量就是并查集中连通分量的数目。
 * 时间复杂度：O(MN×α(MN))，空间复杂度：O(MN)
*/

class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                }
                else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    //* rank 让并查集的树结构更 “矮胖”、少 “瘦高”，减少后续查找根节点的层数，提升整体效率
    vector<int> rank;
    int count;
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int num_r = grid.size();
        if (!num_r) return 0;
        int num_c = grid[0].size();

        UnionFind uf(grid);
        int num_islands = 0;
        for (int r = 0; r < num_r; ++r) {
            for (int c = 0; c < num_c; ++c) {
                if (grid[r][c] == '1') {
                    grid[r][c] = '0';
                    if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * num_c + c, (r-1) * num_c + c);
                    if (r + 1 < num_r && grid[r+1][c] == '1') uf.unite(r * num_c + c, (r+1) * num_c + c);
                    if (c - 1 >= 0 && grid[r][c-1] == '1') uf.unite(r * num_c + c, r * num_c + c - 1);
                    if (c + 1 < num_c && grid[r][c+1] == '1') uf.unite(r * num_c + c, r * num_c + c + 1);
                }
            }
        }

        return uf.getCount();
    }
};

// @lc code=end

