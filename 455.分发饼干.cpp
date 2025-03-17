/*
 * @lc app=leetcode.cn id=455 lang=cpp
 * 贪心
 * [455] 分发饼干
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end(), greater<int>());
        sort(s.begin(), s.end(), greater<int>());
        int result = 0;
        for (int i = 0, j = 0; i < s.size(), j < g.size(); ) {
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
// @lc code=end

