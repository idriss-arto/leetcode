/*
 * @lc app=leetcode.cn id=986 lang=cpp
 * 双指针
 * [986] 区间列表的交集
 */

/*
 * 思路：
 * 初始化i = 0, j = 0,分别指向A和B中的第一个区间
 * 合并区间的右边界，看A中第i区间的右边界和B中第j区间的右边界中的较小值
 * 合并区间的左边界，看A中第i区间的左边界和B中第j区间的左边界中的较大值
 * 如果合并区间的右边界大于等于左边界，则存在，反之不存在
 * 根据合并区间右边界的选中值更新i或j
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        //* 这里不知道合并区间个数，同时后面元素是通过push_back插入的，所以初始化不带容器大小
        vector<vector<int>> result;
        int i = 0, j = 0;
        while(i < firstList.size() && j < secondList.size())
        {
            int start = max(firstList[i][0], secondList[j][0]);
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

