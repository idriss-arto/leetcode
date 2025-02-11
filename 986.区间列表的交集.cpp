/*
 * @lc app=leetcode.cn id=986 lang=cpp
 *  双指针
 * [986] 区间列表的交集
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        while(i < firstList.size() && j < secondList.size())
        {
            int start = max(firstList[i][0], secondList[i][0]);
            int end = min(firstList[i][1], secondList[j][1]);
            if(end == firstList[i][1])
            {
                if(start <= end)
                {
                    result.push_back({start, end});
                }
                i++;
            }
            else
            {
                if(start <= end)
                {
                    result.push_back({start, end});
                }
                j++;
            }
        }
        return result;
    }
};
// @lc code=end

