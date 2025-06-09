/*
 * @lc app=leetcode.cn id=207 lang=cpp
 * 图论
 * [207] 课程表
 */

// @lc code=start
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//* 题解解法
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;    //* 标记节点的状态，0为未搜索，1为搜索中，2为已搜索
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
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

