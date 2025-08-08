/*
 * @lc app=leetcode.cn id=210 lang=cpp
 * 图论，拓扑排序
 ! [210] 课程表 II
 */

/*
 * 思路：
 * 1. 将课程看成图的节点，先修课程看成边。
 * 2. 此题为求拓扑排序。
 * 
 * 有dfs和bfs两种解法
 * dfs解法：没有指向其他节点的边后，当前节点入栈
 * 1. 使用visited数组标记节点的状态，0为未搜索，1为搜索中，2为已搜索。
 * 2. 对于每个未搜索的节点，进行深度优先搜索。
 * 3. 在搜索过程中，如果遇到正在搜索中的节点，则说明存在环，返回false。
 * 4. 如果搜索完成，则将节点标记为已搜索，并入栈。
 * 5. 如果所有节点都搜索完成，则返回栈中排序，否则返回空数组。
 *
 * bfs解法：没有其他节点指向自己后，当前节点入队列
 * 1. 使用入度数组indeg记录每个节点的入度。
 * 2. 将入度为0的节点加入队列。
 * 3. 每次从队列中取出一个节点，加入，并减少其邻接节点的入度。
 * 4. 如果邻接节点的入度变为0，则将其加入队列。
 * 5. 如果所有节点都被访问过，则返回结果数组，否则返回空数组。
*/

// @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

/*
 * 题解解法一，dfs
 * 时间复杂度: O(n+m)，n为节点数，m为边数
 * 空间复杂度: O(n+m)
*/
class Solution {
private:
    //* 存储有向图
    vector<vector<int>> edges;
    //* 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    vector<int> visited;
    //* 用数组来模拟栈，下标 0 为栈底，n-1 为栈顶
    vector<int> result;

    bool dfs(int u) {
        visited[u] = 1;  //* 标记为正在搜索
        for (int v : edges[u]) {
            if (visited[v] == 0) {
                if (!dfs(v)) return false;
            }
            else if (visited[v] == 1) {
                return false;   //* 说明存在环
            }
            else {
                continue;   //* 已经搜索过了
            }
        }
        result.push_back(u);  //* 搜索完成，入栈
        visited[u] = 2;
        return true;    //* 搜索完成，返回true
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses, 0);

        //* 记录边
        for (const auto& info : prerequisites) {
            edges[info[1]].push_back(info[0]);
        }

        //* 对每个节点进行深度优先搜索
        for (int i = 0; i < numCourses; ++i) {
            if (visited[i] == 0) {
                if (!dfs(i)) {
                    return {};   //* 说明存在环，无法完成所有课程
                }
            }
        }

        //* 如果没有环，那么就有拓扑排序
        //! 注意下标 0 为栈底，因此需要将数组反序输出
        reverse(result.begin(), result.end());

        return result;
    }
};

/*
 * 题解解法二，bfs
 * 时间复杂度: O(n+m)，n为节点数，m为边数
 * 空间复杂度: O(n+m)
*/
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses, 0);
        vector<int> result;

        //* 记录边和入度
        for (const auto& info : prerequisites) {
            edges[info[1]].push_back(info[0]);
            indeg[info[0]]++;
        }

        queue<int> uq;
        //* 将入度为0的节点加入队列
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) {
                uq.push(i);
            }
        }

        while (!uq.empty()) {
            int u = uq.front();
            uq.pop();
            result.push_back(u);    //* 将节点加入结果数组
            for (int v : edges[u]) {
                indeg[v]--;         //* 减少邻接节点的入度
                if (indeg[v] == 0) {
                    uq.push(v);     //* 如果入度为0，则加入队列
                }
            }
        }

        if (result.size() == numCourses) {
            return result;          //* 如果所有节点都被访问过，则返回结果数组
        }
        else {
            return {};  //* 否则返回空数组，说明存在环
        }
    }
};
// @lc code=end

