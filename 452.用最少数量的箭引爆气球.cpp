/*
 * @lc app=leetcode.cn id=452 lang=cpp
 * 贪心
 * [452] 用最少数量的箭引爆气球
 */

// @lc code=start
#include <vector>
#include <algorithm>
#include <list>
#include <limits>
using namespace std;
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    }
public:
    /*
     * 题解的代码，
     * 总体思路是还是比较重叠区间，但不用单独记录区间，
     * 直接拿当前气球左边界和之前重叠区间的右边界（代码中用上一气球右边界表示）比较，看能不能一起射掉
     * 可以的话，更新重叠区间右边界即可（代码中没有单独记录右边界，而是改变当前气球右边界）
     * 不可以的话，当前气球用一箭
     * 
     * 我和题解的区别：
     * 我是想比较当前气球和之前重叠区间有无重叠，无重叠的话一箭射掉之前的，再考虑当前气球和之后的气球
     * 题解是先射出一箭，然后根据新来的气球，有重叠的话更新射出的位置，如果没有重叠，就再射出一箭
    */
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; //* points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {      //* 气球i和气球i-1不挨着，注意这里不是>=
                result++;   //* 需要一支箭
            }
            else {          //* 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]);     //* 更新重叠气球最小右边界
            }
        }
        return result;
    }

    /*
     * 我的代码，
     * 总体思路是记录重叠区间
     * 如果没有现有重叠区间的话，当前气球和下一个气球比较看能不能建立一个重叠区间，不能的话一箭射掉当前气球
     * 如果存在现有重叠区间的话，当前气球看和之前的区间重不重合，不重合的话先一箭射掉之前重叠的气球再重新考虑当前气球，重合的话更新重叠区间
     * 最后一个气球单独考虑
     * 
     * 可以看到，思路还是比较明确，但分太多种情况，代码冗余 
    */
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 1) return 1;

        sort(points.begin(), points.end(), cmp);

        int result = 0;
        int start = INT_MIN;
        int end = INT_MIN;
        for (int i = 0; i <= points.size() - 2; i++) {
            //* 如果现在没有现有的重叠区间
            if (start == INT_MIN && end == INT_MIN) {
                //* 没有新的重叠区间
                if (points[i][1] < points[i+1][0]) {
                    //* 当前气球用一箭
                    result++;
                }
                //* 有新的重叠区间
                else {
                    start = points[i+1][0];
                    end = min(points[i][1], points[i+1][1]);
                    //* 直接跳过i+1，去判断i+2
                    i++;
                    continue;
                }
            }
            //* 现在存在现有的重叠区间
            else {
                //* 现在的气球和已有的重叠区间也有重叠，更新
                if (points[i][0] >= start && points[i][0] <= end) {
                    start = points[i][0];
                    end = min(end, points[i][1]);
                }
                //* 现在的气球和已有的重叠区间没有重叠
                else {
                    //* 先一箭把之前重叠的射掉
                    result++;
                    start = INT_MIN;
                    end = INT_MIN;
                    //* 重新进入当前节点
                    i--;
                }
            }
        }
        //* 最后一个气球单独判断
        if (start == INT_MIN && end == INT_MIN) {
            //* 没有现有的重叠区间，一箭射掉最后一个即可
            result++;
        }
        else {
            //* 先一箭把之前重叠的射掉
            result++;
            //* 最后一个气球和已有的重叠区间没有重叠，需要补一箭
            if (!(points.back()[0] >= start && points.back()[0] <= end)) result++;
        }
        return result;
    }
};
// @lc code=end

