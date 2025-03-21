/*
 * @lc app=leetcode.cn id=406 lang=cpp
 * 贪心
 * [406] 根据身高重建队列
 */

/*
 * 遇到两个维度权衡的时候，
 ! 一定要先确定一个维度，再确定另一个维度。
 * 如果两个维度一起考虑一定会顾此失彼。
*/

// @lc code=start
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
//* 版本一
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp);
        vector<vector<int>> que;
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            que.insert(que.begin() + position, people[i]);
        }
        return que;
    }
};

//* 版本二，用list结构，插入效率更高
class Solution {
public:
    //* 身高从大到小排（身高相同k小的站前面）
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp);
        list<vector<int>> que;                      //* list底层是链表实现，插入效率比vector高的多
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];            //* 插入到下标为position的位置
            std::list<vector<int>>::iterator it = que.begin();
            while (position--) {                    //* 寻找在插入位置
                it++;
            }
            que.insert(it, people[i]);
        }
        return vector<vector<int>>(que.begin(), que.end());
    }
};
// @lc code=end

