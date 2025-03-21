/*
 * @lc app=leetcode.cn id=435 lang=cpp
 * 贪心
 * [435] 无重叠区间
 */

//* 和452殊途同归

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    //* 按照区间右边界排序
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
    
    //* 思路，记录当前右边界，新来的有重合就扔掉，没有重合则更新右边界
    //* 这里遇到重叠的不更新右边界是因为用的右边界排序，一开始的右边界确定是最小的
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 1;  //* 记录非交叉区间的个数
        int end = intervals[0][1];  //* 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= end) {
                end = intervals[i][1];
                count++;
            }
        }
        //! 注意这里
        return intervals.size() - count;
    }
};

class Solution2 {
public:
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];     //* 改为左边界排序
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 0;  //* 注意这里从0开始，因为是记录重叠区间
        int end = intervals[0][1];  //* 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {   
            if (intervals[i][0] >= end)  end = intervals[i][1];     //* 无重叠的情况
            else {  //* 重叠情况 
                end = min(end, intervals[i][1]);
                count++;
            }
        }
        //! 注意这里
        return count;
    }
};
// @lc code=end

