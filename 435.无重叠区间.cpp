/*
 * @lc app=leetcode.cn id=435 lang=cpp
 * 贪心，重叠区间
 ! [435] 无重叠区间
 */

/*
 * 思路：
 * 可以以左边界递增排序，也可以以右边界递增排序，不影响以下两种方案
 * 一：
 * count表示需要删除的区间数量，初始化为0。
 * 比较新来的区域起点和当前重叠区间终点，
 * 如果有重合，则count++，重置重叠区间终点，
 * 无重合，则重叠区间设为新来区间。
 * 最后返回count。
 * 
 * 二：
 * count表示最后留下的无重叠区间数量，初始化为1。
 * 比较新来的区域起点和当前重叠区间终点，
 * 如果有重合，则重置重叠区间终点，
 * 无重合，则count++，重叠区间设为新来区间。
 * 最后返回intervals.size() - count。
*/

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
        int count = 1;              //* 记录非交叉区间的个数
        int end = intervals[0][1];  //* 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {
            //* 无重叠
            if (intervals[i][0] >= end) {
                end = intervals[i][1];
                count++;
            }
            //* 有重叠
            else {
                //* end = min(end, intervals[i][1]);
                //* 这里遇到重叠的不更新右边界是因为用的右边界排序，一开始的右边界确定是最小的
            }
        }
        //! 注意这里
        return intervals.size() - count;
    }
};

class Solution {
public:
    //* 按照区间左边界排序
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 0;              //* 注意这里从0开始，因为是记录重叠区间
        int end = intervals[0][1];  //* 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {
            //* 无重叠的情况
            if (intervals[i][0] >= end)  {
                end = intervals[i][1];
            }   
            //* 重叠情况
            else {                   
                end = min(end, intervals[i][1]);
                count++;
            }
        }
        //! 注意这里
        return count;
    }
};
// @lc code=end

