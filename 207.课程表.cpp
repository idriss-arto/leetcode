/*
 * @lc app=leetcode.cn id=207 lang=cpp
 * 图论
 * [207] 课程表
 */

/*
 * 思路：
 * 1. 将课程看成图的节点，先修课程看成边。
 * 2. 如果图中存在环，则无法完成所有课程。
 * 
 * 有dfs和bfs两种解法
 * dfs解法：没有指向其他节点的边后，当前节点入栈
 * 1. 使用visited数组标记节点的状态，0为未搜索，1为搜索中，2为已搜索。
 * 2. 对于每个未搜索的节点，进行深度优先搜索。
 * 3. 在搜索过程中，如果遇到正在搜索中的节点，则说明存在环，返回false。
 * 4. 如果搜索完成，则将节点标记为已搜索。
 * 5. 如果所有节点都搜索完成，则返回true。
 *
 * bfs解法：没有其他节点指向自己后，当前节点入队列
 * 1. 使用入度数组indeg记录每个节点的入度。
 * 2. 将入度为0的节点加入队列。
 * 3. 每次从队列中取出一个节点，减少其邻接节点的入度。
 * 4. 如果邻接节点的入度变为0，则将其加入队列。
 * 5. 如果所有节点都被访问过，则返回true，否则返回false。
*/

// @lc code=start
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
 * 题解解法一，dfs
 * 时间复杂度: O(n+m)，n为节点数，m为边数
 * 空间复杂度: O(n+m)
*/
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;    //* 标记节点的状态，0为未搜索，1为搜索中，2为已搜索
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
            //* 注意这里if-else必须判断是否为0或者1，因为还有2
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v: edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        return visited == numCourses;
    }
};

//* 我的解法，深度优先搜索
//* 效果很差
class Solution {
public:
    unordered_map<int, vector<int>> edges;
    unordered_set<int> visited;

    bool dfs(int course, set<int> set) {
        if (!edges.count(course) || visited.count(course)) return true;
        else {
            for (int& tmp : edges[course]) {
                if (set.count(tmp)) return false;

                set.insert(course);
                if (!dfs(tmp, set)) return false;
            }
            visited.insert(course);
            return true;
        }
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        for (int i = 0; i < prerequisites.size(); i++) {
            int course = prerequisites[i][0];
            int preCourse = prerequisites[i][1];

            edges[course].push_back(preCourse);
        }

        for (auto it : edges) {
            int course = it.first;
            set<int> set;
            set.insert(course);

            if (!dfs(course, set)) return false;
        }
        return true;
    }
};
// @lc code=end

