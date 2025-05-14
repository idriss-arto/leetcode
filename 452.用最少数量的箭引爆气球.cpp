/*
 * @lc app=leetcode.cn id=452 lang=cpp
 * 贪心，重叠区间
 ! [452] 用最少数量的箭引爆气球
 */

// @lc code=start
#include <vector>
#include <algorithm>
#include <list>
#include <limits>
using namespace std;

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
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1;     //* points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            //* 气球i和气球i-1不挨着，注意这里不是>=
            if (points[i][0] > points[i - 1][1]) {
                result++;   //* 需要一支新箭
            }
            //* 气球i和气球i-1挨着
            else {
                points[i][1] = min(points[i - 1][1], points[i][1]);     //* 更新重叠气球最小右边界
            }
        }
        return result;
    }
};

/*
 * 我的代码，
 * 总体思路是记录重叠区间
 * 当前气球看和之前的区间重不重合，
 * 重合的话更新重叠区间，
 * 不重合的话先一箭射掉之前重叠的气球再重新考虑当前气球，
 * 最后一个气球单独考虑。
*/
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() <= 1) return points.size();

        sort(points.begin(), points.end(), cmp);

        int result = 0;
        int start = points[0][0];
        int end = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            //* 当前气球和现有重叠区间有重合
            if (points[i][0] >= start && points[i][0] <= end) {
                //* 更新重叠区间起点和终点
                start = points[i][0];
                end = min(end, points[i][1]);
            }
            //* 当前气球和现有重叠区间没有重合
            else {
                //* 先一箭把之前重叠的气球都射了
                result++;

                //* 以当前气球重新设置重叠区间
                start = points[i][0];
                end = points[i][1];
            }
                            
            //* 如果是最后一个气球，补一箭
            if (i == points.size() - 1) result++;
        }
        return result;
    }
};
// @lc code=end

