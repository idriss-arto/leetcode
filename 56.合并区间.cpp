/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * 贪心，重叠区间
 * [56] 合并区间
 */

/*
 * 思路：
 * 用左边界排序后（右边界也可以，只是判断重叠后的操作有区别），
 * 用当前区间的开头与现有区间的结尾做重叠判断，
 * 重叠的话，重叠区间结尾更新。
 * 不重叠的话，记录现有重叠区间，再将重叠区间设置为当前区间。
 * 遍历完所有区间后，最后补记最后一个重叠区间。
*/

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) return intervals;
        sort(intervals.begin(), intervals.end(), cmp);
        //* 排序的参数也可以使用lambda表达式
        // sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});

        vector<vector<int>> result;
        int start = intervals[0][0];
        int end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            //* 区间重叠
            if (intervals[i][0] <= end) {
                end = max(end, intervals[i][1]);
            }
            //* 区间不重叠
            else {
                result.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        //* 补记最后一个区间
        result.push_back({start, end});

        return result;
    }
};
// @lc code=end

