/*
 * @lc app=leetcode.cn id=332 lang=cpp
 * 回溯，欧拉图
 * [332] 重新安排行程
 */

// @lc code=start
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

//! 回溯法，掌握！
/*
 * 思路：
 * 用 dfs 遍历，从 JFK 开始，尝试所有可能的选择，
 * 这需要知道当前可以飞哪些城市，需要构建邻接表。
 * 根据当前选择，往下递归，尝试找出第一个用完机票的路径，如果找不出来，返回false，否则，返回true。
 * 访问过的边要删掉。比如，北京飞广州，到了广州，北京的邻居list中删掉广州。
 * 为什么要返回真假，因为要用它判断要不要提前回溯，在该分支走不下去，就要离开。
 * 我们选择飞入的城市，如果困住了，就是飞错了，要回溯，
 * 将北京的邻居list中删除的广州恢复回来，不飞广州了，飞别的试试，离开当前分支，切入别的分支，继续探索路径。
*/
class Solution2 {
private:
//* unordered_map<出发机场, map<到达机场, 航班次数>> targets
    unordered_map<string, map<string, int>> targets;
    bool backtracking(int ticketNum, vector<string>& result) {
        if (result.size() == ticketNum + 1) {
            return true;
        }
        //! 一定要加上引用即 & target，因为后面有对 target.second 做减减操作
        //* result[result.size() - 1] 即当前所处的城市，也可用result.back表示
        for (pair<const string, int>& target : targets[result[result.size() - 1]]) {
            if (target.second > 0 ) {           //* 记录这张机票是否用过了
                result.push_back(target.first);
                target.second--;
                if (backtracking(ticketNum, result)) return true;   //* 成功
                result.pop_back();  //* 失败，尝试下一张机票
                target.second++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        targets.clear();
        vector<string> result;
        for (const vector<string>& vec : tickets) {
            targets[vec[0]][vec[1]]++;      //* 记录映射关系
        }
        result.push_back("JFK");            //* 起始机场
        backtracking(tickets.size(), result);
        return result;
    }
};

//* 欧拉路径，Hierholzer 算法
/*
 * 从起点出发，进行深度优先搜索。
 * 每次沿着某条边从某个顶点移动到另外一个顶点的时候，都需要删除这条边。
 * 如果没有可移动的路径，则将所在节点加入到栈中，并返回。
 * 对于当前节点而言，从它的每一个非「死胡同」分支出发进行深度优先搜索，都将会搜回到当前节点。
 * 而从它的「死胡同」分支出发进行深度优先搜索将不会搜回到当前节点。
 * 也就是说当前节点的死胡同分支将会优先于其他非「死胡同」分支入栈。
*/
class Solution {
private:
    //* 使用greater实现升序排列
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> mymap;
    vector<string> itinerary;

    void dfs(const string& airport) {
        while (!mymap[airport].empty()) {
            string nextAirport = mymap[airport].top();
            mymap[airport].pop();
            dfs(nextAirport);
        }
        itinerary.push_back(airport);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto ticket : tickets) {
            mymap[ticket[0]].push(ticket[1]);
        }

        dfs("JFK");
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }
};

// int main() {
//     Solution s;
//     vector<vector<string>> tickets;
//     tickets.push_back({"JFK","SFO"});
//     tickets.push_back({"JFK","ATL"});
//     tickets.push_back({"SFO","ATL"});
//     tickets.push_back({"ATL","JFK"});
//     tickets.push_back({"ATL","SFO"});
//     s.findItinerary(tickets);
// }
// @lc code=end

