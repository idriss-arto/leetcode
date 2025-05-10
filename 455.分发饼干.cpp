/*
 * @lc app=leetcode.cn id=455 lang=cpp
 * 贪心
 * [455] 分发饼干
 */

/*
 * 贪心思路：
 * 一：大饼干喂大胃口
 * 二：小饼干喂小胃口
*/

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

//* 贪心，大饼干喂大胃口
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        //* 递减
        sort(g.begin(), g.end(), greater<int>());
        sort(s.begin(), s.end(), greater<int>());
        int result = 0;
        for (int i = 0, j = 0; i < s.size() && j < g.size(); ) {
            if (s[i] >= g[j]) {
                i++;
                j++;
                result++;
            }
            else {
                j++;
            }
        }
        return result;
    }
};

//* 贪心，小饼干喂小胃口
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        //* 默认使用less<int>()，递增
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        for (int i = 0, j = 0; i < s.size(), j < g.size(); ) {
            if (s[i] >= g[j]) {
                i++;
                j++;
                result++;
            }
            else {
                i++;
            }
        }
        return result;
    }
};
// @lc code=end

