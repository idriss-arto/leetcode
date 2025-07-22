/*
 * @lc app=leetcode.cn id=118 lang=cpp
 * 动态规划
 * [118] 杨辉三角 
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        for (int i = 1; i <= numRows; i++) {
            if (i == 1) {
                result.push_back({1});
                continue;
            }

            vector<int>& pre = result.back();
            vector<int> now;

            //* 每一层的首尾元素特殊处理
            now.push_back(1);
            for (int j = 1; j < i - 1; j++) {
                now.push_back(pre[j-1] + pre[j]);
            }
            now.push_back(1);
            
            result.push_back(now);
        }
        return result;
    }
};
// @lc code=end

