/*
 * @lc app=leetcode.cn id=332 lang=cpp
 * 回溯
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

class Solution {
private:
    // 使用greater实现升序排列
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

//! 回溯法
class Solution2 {
private:
//* unordered_map<出发机场, map<到达机场, 航班次数>> targets
    unordered_map<string, map<string, int>> targets;
    bool backtracking(int ticketNum, vector<string>& result) {
        if (result.size() == ticketNum + 1) {
            return true;
        }
        for (pair<const string, int>& target : targets[result[result.size() - 1]]) {
            if (target.second > 0 ) {           //* 记录到达机场是否飞过了
                result.push_back(target.first);
                target.second--;
                if (backtracking(ticketNum, result)) return true;
                result.pop_back();
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

