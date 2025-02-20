/*
 * @lc app=leetcode.cn id=454 lang=cpp
 * 哈希
 * [454] 四数相加 II
 */

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map <int, int> umap;
        int count = 0;
        for (int i : nums1) {
            for (int j : nums2) {
                umap[i + j]++;
            }
        }
        for (int a : nums3) {
            for (int b : nums4) {
                if (umap.find(0 - (a + b)) != umap.end()) {
                    count += umap[0 - (a + b)];
                }
            }
        }
        return count;
    }
};
// @lc code=end

